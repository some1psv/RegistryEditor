/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/apputil.h>

#include <vita2d.h>*/
#include "main.h"
#include "ime_dialog.h"

// Store positions so that the right item is selected when the user presses the back button
int topList[10] = {0};
int curPosList[10] = {0};
int posInd = 0;

char* regData[][3] =
{
	{"/REGISTRY/ERROR/", "err_enable", "\x01"},
	{"/REGISTRY/ERROR/00/", "info", "\x03"},
	{"/REGISTRY/ERROR/00/", "value", "\x03"},
	{"/REGISTRY/ERROR/01/", "info", "\x03"},
	{"/REGISTRY/ERROR/01/", "value", "\x03"},
	{"/REGISTRY/ERROR/02/", "info", "\x03"},
	{"/REGISTRY/ERROR/02/", "value", "\x03"},
	{"/REGISTRY/ERROR/03/", "info", "\x03"},
	{"/REGISTRY/ERROR/03/", "value", "\x03"},
	{"/REGISTRY/ERROR/04/", "info", "\x03"},
	{"/REGISTRY/ERROR/04/", "value", "\x03"},
	{"/REGISTRY/ERROR/05/", "info", "\x03"},
	{"/REGISTRY/ERROR/05/", "value", "\x03"},
	{"/REGISTRY/ERROR/06/", "info", "\x03"},
	{"/REGISTRY/ERROR/06/", "value", "\x03"},
	{"/REGISTRY/ERROR/07/", "info", "\x03"},
	{"/REGISTRY/ERROR/07/", "value", "\x03"},
	{"/REGISTRY/ERROR/08/", "info", "\x03"},
	{"/REGISTRY/ERROR/08/", "value", "\x03"},
	{"/REGISTRY/ERROR/09/", "info", "\x03"},
	{"/REGISTRY/ERROR/09/", "value", "\x03"},
	{"/CONFIG/SYSTEM/", "flight_mode", "\x01"},
	{"/CONFIG/SYSTEM/", "username", "\x02"},
	{"/CONFIG/SYSTEM/", "language", "\x01"},
	{"/CONFIG/SYSTEM/", "button_assign", "\x01"},
	{"/CONFIG/SYSTEM/", "key_pad", "\x01"},
	{"/CONFIG/SYSTEM/", "init_settings", "\x01"},
	{"/CONFIG/SYSTEM/", "initialize", "\x01"},
	{"/CONFIG/SYSTEM/", "hdmi_use_cec", "\x01"},
	{"/CONFIG/SYSTEM/", "controller_vibration", "\x01"},
	{"/CONFIG/SYSTEM/", "skip_patch_download", "\x01"},
	{"/CONFIG/SYSTEM/", "debug_mode", "\x01"},
	{"/CONFIG/SYSTEM/", "launch_check", "\x01"},
	{"/CONFIG/SYSTEM/", "dualshock4_usb", "\x01"},
	{"/CONFIG/SYSTEM/UPDATE/", "server_url", "\x02"},
	{"/CONFIG/SYSTEM/UPDATE/", "pup_list_flag", "\x01"},
	{"/CONFIG/SYSTEM/UPDATE/", "enable_media", "\x01"},
	{"/CONFIG/SYSTEM/UPDATE/", "enable_host0", "\x01"},
	{"/CONFIG/SYSTEM/UPDATE/", "enable_tool_pup_check", "\x01"},
	{"/CONFIG/SYSTEM/UPDATE/", "idu_auto_start", "\x01"},
	{"/CONFIG/SYSTEM/CONSOLE_INFO/", "inoperative_time", "\x01"},
	{"/CONFIG/SHELL/", "bgm", "\x01"},
	{"/CONFIG/SHELL/", "notification", "\x01"},
	{"/CONFIG/SHELL/", "notify_ps_button", "\x01"},
	{"/CONFIG/SHELL/", "notify_sound", "\x01"},
	{"/CONFIG/SHELL/", "notify_msg", "\x01"},
	{"/CONFIG/SHELL/", "mic_mute", "\x01"},
	{"/CONFIG/SHELL/", "voice_priority", "\x01"},
	{"/CONFIG/SHELL/", "voice_ducking", "\x01"},
	{"/CONFIG/SHELL/", "livearea_help", "\x01"},
	{"/CONFIG/SHELL/", "livearea_plus_help", "\x01"},
	{"/CONFIG/SHELL/", "home_help", "\x01"},
	{"/CONFIG/SHELL/", "event_help", "\x01"},
	{"/CONFIG/SHELL/", "edit_help", "\x01"},
	{"/CONFIG/SHELL/", "touch_emulation", "\x01"},
	{"/CONFIG/SHELL/", "touch_emulation_help", "\x01"},
	{"/CONFIG/SHELL/", "trc_check_notify", "\x01"},
	{"/CONFIG/SHELL/", "playlog_clock", "\x01"},
	{"/CONFIG/SHELL/", "test_crash", "\x01"},
	{"/CONFIG/SHELL/", "shell_auto_create_folder", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "passcode", "\x02"},
	{"/CONFIG/SECURITY/PARENTAL/", "content_start_control", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "browser_start_control", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "email_start_control", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "restrict_mode", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "restrict_duration_one", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "restrict_duration_sun", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "restrict_duration_mon", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "restrict_duration_tue", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "restrict_duration_wed", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "restrict_duration_thu", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "restrict_duration_fri", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "restrict_duration_sat", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "change_date", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "change_duration", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "remaining_date", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "remaining_duration", "\x01"},
	{"/CONFIG/SECURITY/PARENTAL/", "store_start_control", "\x01"},
	{"/CONFIG/SECURITY/SCREEN_LOCK/", "passcode", "\x02"},
	{"/CONFIG/SECURITY/SCREEN_LOCK/", "times_left", "\x01"},
	{"/CONFIG/SECURITY/SCREEN_LOCK/", "input_lock_time", "\x01"},
	{"/CONFIG/DTCPIP/", "devcert", "\x03"},
	{"/CONFIG/DATE/", "time_zone", "\x01"},
	{"/CONFIG/DATE/", "date_format", "\x01"},
	{"/CONFIG/DATE/", "time_format", "\x01"},
	{"/CONFIG/DATE/", "auto_summer_time", "\x01"},
	{"/CONFIG/DATE/", "summer_time", "\x01"},
	{"/CONFIG/DATE/", "set_automatically", "\x01"},
	{"/CONFIG/ACCESSIBILITY/", "zoom", "\x01"},
	{"/CONFIG/ACCESSIBILITY/", "invert_color", "\x01"},
	{"/CONFIG/ACCESSIBILITY/", "large_text", "\x01"},
	{"/CONFIG/ACCESSIBILITY/", "bold_text", "\x01"},
	{"/CONFIG/ACCESSIBILITY/", "contrast", "\x01"},
	{"/CONFIG/ACCESSIBILITY/", "keyremap_enable", "\x01"},
	{"/CONFIG/ACCESSIBILITY/", "keyremap_data", "\x03"},
	{"/CONFIG/ACCESSIBILITY/", "shortcut", "\x01"},
	{"/CONFIG/ACCESSIBILITY/CC/", "enable_cc", "\x01"},
	{"/CONFIG/ACCESSIBILITY/CC/", "content_specific", "\x01"},
	{"/CONFIG/ACCESSIBILITY/CC/", "char_color", "\x01"},
	{"/CONFIG/ACCESSIBILITY/CC/", "char_opacity", "\x01"},
	{"/CONFIG/ACCESSIBILITY/CC/", "char_size", "\x01"},
	{"/CONFIG/ACCESSIBILITY/CC/", "font_type", "\x01"},
	{"/CONFIG/ACCESSIBILITY/CC/", "char_edge", "\x01"},
	{"/CONFIG/ACCESSIBILITY/CC/", "char_edge_color", "\x01"},
	{"/CONFIG/ACCESSIBILITY/CC/", "char_bg_color", "\x01"},
	{"/CONFIG/ACCESSIBILITY/CC/", "char_bg_opacity", "\x01"},
	{"/CONFIG/ACCESSIBILITY/CC/", "window_color", "\x01"},
	{"/CONFIG/ACCESSIBILITY/CC/", "window_opacity", "\x01"},
	{"/CONFIG/POWER_SAVING/", "suspend_interval", "\x01"},
	{"/CONFIG/POWER_SAVING/", "controller_off_interval", "\x01"},
	{"/CONFIG/DISPLAY/", "brightness", "\x01"},
	{"/CONFIG/DISPLAY/", "hdmi_resolution_mode", "\x01"},
	{"/CONFIG/DISPLAY/", "hdmi_out_scaling_ratio", "\x01"},
	{"/CONFIG/DISPLAY/", "dimming_interval", "\x01"},
	{"/CONFIG/DISPLAY/", "color_space_mode", "\x01"},
	{"/CONFIG/DISPLAY/", "rgb_range_mode", "\x01"},
	{"/CONFIG/SOUND/", "main_volume", "\x01"},
	{"/CONFIG/SOUND/", "master_volume", "\x01"},
	{"/CONFIG/SOUND/", "avls", "\x01"},
	{"/CONFIG/SOUND/", "avls_timer", "\x01"},
	{"/CONFIG/SOUND/", "sound_output", "\x01"},
	{"/CONFIG/SOUND/", "speaker_mute", "\x01"},
	{"/CONFIG/IME/", "auto_capitalization", "\x01"},
	{"/CONFIG/IME/", "last_unit", "\x01"},
	{"/CONFIG/IME/", "ui_hint", "\x01"},
	{"/CONFIG/IME/", "predictive_text", "\x01"},
	{"/CONFIG/IME/", "kb_type", "\x01"},
	{"/CONFIG/IME/", "kb_zh_t_input_method", "\x01"},
	{"/CONFIG/IME/", "kb_ja_input_method", "\x01"},
	{"/CONFIG/IME/", "kb_key_repeat_start", "\x01"},
	{"/CONFIG/IME/", "kb_key_repeat_interval", "\x01"},
	{"/CONFIG/IME/UK_ENGLISH/", "input_type", "\x01"},
	{"/CONFIG/IME/US_ENGLISH/", "input_type", "\x01"},
	{"/CONFIG/IME/DANISH/", "input_type", "\x01"},
	{"/CONFIG/IME/GERMAN/", "input_type", "\x01"},
	{"/CONFIG/IME/SPANISH/", "input_type", "\x01"},
	{"/CONFIG/IME/FINNISH/", "input_type", "\x01"},
	{"/CONFIG/IME/FRENCH/", "input_type", "\x01"},
	{"/CONFIG/IME/ITALIAN/", "input_type", "\x01"},
	{"/CONFIG/IME/JAPANESE/", "input_type", "\x01"},
	{"/CONFIG/IME/KOREAN/", "input_type", "\x01"},
	{"/CONFIG/IME/DUTCH/", "input_type", "\x01"},
	{"/CONFIG/IME/NORWEGIAN/", "input_type", "\x01"},
	{"/CONFIG/IME/POLISH/", "input_type", "\x01"},
	{"/CONFIG/IME/PORTUGUESE/", "input_type", "\x01"},
	{"/CONFIG/IME/RUSSIAN/", "input_type", "\x01"},
	{"/CONFIG/IME/SWEDISH/", "input_type", "\x01"},
	{"/CONFIG/IME/TRADITIONAL_CHINESE_HK/", "input_type", "\x01"},
	{"/CONFIG/IME/TRADITIONAL_CHINESE_TW/", "input_type", "\x01"},
	{"/CONFIG/IME/SIMPLIFIED_CHINESE/", "input_type", "\x01"},
	{"/CONFIG/IME/BRAZILIAN_PORTUGUESE/", "input_type", "\x01"},
	{"/CONFIG/IME/TURKISH/", "input_type", "\x01"},
	{"/CONFIG/BT/", "bt_enable", "\x01"},
	{"/CONFIG/BT/", "bt_config", "\x01"},
	{"/CONFIG/BT/", "bt_mic", "\x01"},
	{"/CONFIG/BT/00/", "info", "\x03"},
	{"/CONFIG/BT/01/", "info", "\x03"},
	{"/CONFIG/BT/02/", "info", "\x03"},
	{"/CONFIG/BT/03/", "info", "\x03"},
	{"/CONFIG/BT/04/", "info", "\x03"},
	{"/CONFIG/BT/05/", "info", "\x03"},
	{"/CONFIG/BT/06/", "info", "\x03"},
	{"/CONFIG/BT/07/", "info", "\x03"},
	{"/CONFIG/BT/08/", "info", "\x03"},
	{"/CONFIG/BT/09/", "info", "\x03"},
	{"/CONFIG/BT/10/", "info", "\x03"},
	{"/CONFIG/BT/11/", "info", "\x03"},
	{"/CONFIG/BT/12/", "info", "\x03"},
	{"/CONFIG/BT/13/", "info", "\x03"},
	{"/CONFIG/BT/14/", "info", "\x03"},
	{"/CONFIG/BT/15/", "info", "\x03"},
	{"/CONFIG/NET/", "wifi_flag", "\x01"},
	{"/CONFIG/NET/", "net_flag", "\x01"},
	{"/CONFIG/NET/", "wifi_config", "\x01"},
	{"/CONFIG/NET/", "wifi_power_save", "\x01"},
	{"/CONFIG/NET/", "adhoc_channel", "\x01"},
	{"/CONFIG/NET/", "adhoc_ssid", "\x02"},
	{"/CONFIG/NET/", "ap_auto_config", "\x01"},
	{"/CONFIG/NET/", "enable_impose_scanlist", "\x01"},
	{"/CONFIG/NET/", "enable_tcpdump_log", "\x01"},
	{"/CONFIG/NET/", "fake_3g_if", "\x01"},
	{"/CONFIG/NET/", "icm_type", "\x01"},
	{"/CONFIG/NET/", "emulation_type", "\x01"},
	{"/CONFIG/NET/", "emulation_if", "\x01"},
	{"/CONFIG/NET/", "pspnet_adhoc_ssid_prefix", "\x02"},
	{"/CONFIG/NET/", "primary_dns_for_3g", "\x02"},
	{"/CONFIG/NET/", "secondary_dns_for_3g", "\x02"},
	{"/CONFIG/NET/", "ssl_cert_ignorable", "\x01"},
	{"/CONFIG/NET/", "wol_config", "\x01"},
	{"/CONFIG/NET/01/COMMON/", "conf_flag", "\x01"},
	{"/CONFIG/NET/01/COMMON/", "conf_type", "\x01"},
	{"/CONFIG/NET/01/COMMON/", "conf_name", "\x02"},
	{"/CONFIG/NET/01/COMMON/", "conf_serial_no", "\x01"},
	{"/CONFIG/NET/01/COMMON/", "enable_auto_connect", "\x01"},
	{"/CONFIG/NET/01/COMMON/", "mtu", "\x01"},
	{"/CONFIG/NET/01/COMMON/", "device", "\x01"},
	{"/CONFIG/NET/01/COMMON/", "ether_mode", "\x01"},
	{"/CONFIG/NET/01/WIFI/", "ssid", "\x02"},
	{"/CONFIG/NET/01/WIFI/", "wifi_security", "\x01"},
	{"/CONFIG/NET/01/WIFI/", "wep_key", "\x02"},
	{"/CONFIG/NET/01/WIFI/", "wpa_key", "\x02"},
	{"/CONFIG/NET/01/IP/", "ip_config", "\x01"},
	{"/CONFIG/NET/01/IP/", "dhcp_hostname", "\x02"},
	{"/CONFIG/NET/01/IP/", "auth_name", "\x02"},
	{"/CONFIG/NET/01/IP/", "auth_key", "\x02"},
	{"/CONFIG/NET/01/IP/", "ip_address", "\x02"},
	{"/CONFIG/NET/01/IP/", "netmask", "\x02"},
	{"/CONFIG/NET/01/IP/", "default_route", "\x02"},
	{"/CONFIG/NET/01/IP/", "dns_flag", "\x01"},
	{"/CONFIG/NET/01/IP/", "primary_dns", "\x02"},
	{"/CONFIG/NET/01/IP/", "secondary_dns", "\x02"},
	{"/CONFIG/NET/01/APP/", "http_proxy_flag", "\x01"},
	{"/CONFIG/NET/01/APP/", "http_proxy_server", "\x02"},
	{"/CONFIG/NET/01/APP/", "http_proxy_port", "\x01"},
	{"/CONFIG/NET/02/COMMON/", "conf_flag", "\x01"},
	{"/CONFIG/NET/02/COMMON/", "conf_type", "\x01"},
	{"/CONFIG/NET/02/COMMON/", "conf_name", "\x02"},
	{"/CONFIG/NET/02/COMMON/", "conf_serial_no", "\x01"},
	{"/CONFIG/NET/02/COMMON/", "enable_auto_connect", "\x01"},
	{"/CONFIG/NET/02/COMMON/", "mtu", "\x01"},
	{"/CONFIG/NET/02/COMMON/", "device", "\x01"},
	{"/CONFIG/NET/02/COMMON/", "ether_mode", "\x01"},
	{"/CONFIG/NET/02/WIFI/", "ssid", "\x02"},
	{"/CONFIG/NET/02/WIFI/", "wifi_security", "\x01"},
	{"/CONFIG/NET/02/WIFI/", "wep_key", "\x02"},
	{"/CONFIG/NET/02/WIFI/", "wpa_key", "\x02"},
	{"/CONFIG/NET/02/IP/", "ip_config", "\x01"},
	{"/CONFIG/NET/02/IP/", "dhcp_hostname", "\x02"},
	{"/CONFIG/NET/02/IP/", "auth_name", "\x02"},
	{"/CONFIG/NET/02/IP/", "auth_key", "\x02"},
	{"/CONFIG/NET/02/IP/", "ip_address", "\x02"},
	{"/CONFIG/NET/02/IP/", "netmask", "\x02"},
	{"/CONFIG/NET/02/IP/", "default_route", "\x02"},
	{"/CONFIG/NET/02/IP/", "dns_flag", "\x01"},
	{"/CONFIG/NET/02/IP/", "primary_dns", "\x02"},
	{"/CONFIG/NET/02/IP/", "secondary_dns", "\x02"},
	{"/CONFIG/NET/02/APP/", "http_proxy_flag", "\x01"},
	{"/CONFIG/NET/02/APP/", "http_proxy_server", "\x02"},
	{"/CONFIG/NET/02/APP/", "http_proxy_port", "\x01"},
	{"/CONFIG/NET/03/COMMON/", "conf_flag", "\x01"},
	{"/CONFIG/NET/03/COMMON/", "conf_type", "\x01"},
	{"/CONFIG/NET/03/COMMON/", "conf_name", "\x02"},
	{"/CONFIG/NET/03/COMMON/", "conf_serial_no", "\x01"},
	{"/CONFIG/NET/03/COMMON/", "enable_auto_connect", "\x01"},
	{"/CONFIG/NET/03/COMMON/", "mtu", "\x01"},
	{"/CONFIG/NET/03/COMMON/", "device", "\x01"},
	{"/CONFIG/NET/03/COMMON/", "ether_mode", "\x01"},
	{"/CONFIG/NET/03/WIFI/", "ssid", "\x02"},
	{"/CONFIG/NET/03/WIFI/", "wifi_security", "\x01"},
	{"/CONFIG/NET/03/WIFI/", "wep_key", "\x02"},
	{"/CONFIG/NET/03/WIFI/", "wpa_key", "\x02"},
	{"/CONFIG/NET/03/IP/", "ip_config", "\x01"},
	{"/CONFIG/NET/03/IP/", "dhcp_hostname", "\x02"},
	{"/CONFIG/NET/03/IP/", "auth_name", "\x02"},
	{"/CONFIG/NET/03/IP/", "auth_key", "\x02"},
	{"/CONFIG/NET/03/IP/", "ip_address", "\x02"},
	{"/CONFIG/NET/03/IP/", "netmask", "\x02"},
	{"/CONFIG/NET/03/IP/", "default_route", "\x02"},
	{"/CONFIG/NET/03/IP/", "dns_flag", "\x01"},
	{"/CONFIG/NET/03/IP/", "primary_dns", "\x02"},
	{"/CONFIG/NET/03/IP/", "secondary_dns", "\x02"},
	{"/CONFIG/NET/03/APP/", "http_proxy_flag", "\x01"},
	{"/CONFIG/NET/03/APP/", "http_proxy_server", "\x02"},
	{"/CONFIG/NET/03/APP/", "http_proxy_port", "\x01"},
	{"/CONFIG/NET/04/COMMON/", "conf_flag", "\x01"},
	{"/CONFIG/NET/04/COMMON/", "conf_type", "\x01"},
	{"/CONFIG/NET/04/COMMON/", "conf_name", "\x02"},
	{"/CONFIG/NET/04/COMMON/", "conf_serial_no", "\x01"},
	{"/CONFIG/NET/04/COMMON/", "enable_auto_connect", "\x01"},
	{"/CONFIG/NET/04/COMMON/", "mtu", "\x01"},
	{"/CONFIG/NET/04/COMMON/", "device", "\x01"},
	{"/CONFIG/NET/04/COMMON/", "ether_mode", "\x01"},
	{"/CONFIG/NET/04/WIFI/", "ssid", "\x02"},
	{"/CONFIG/NET/04/WIFI/", "wifi_security", "\x01"},
	{"/CONFIG/NET/04/WIFI/", "wep_key", "\x02"},
	{"/CONFIG/NET/04/WIFI/", "wpa_key", "\x02"},
	{"/CONFIG/NET/04/IP/", "ip_config", "\x01"},
	{"/CONFIG/NET/04/IP/", "dhcp_hostname", "\x02"},
	{"/CONFIG/NET/04/IP/", "auth_name", "\x02"},
	{"/CONFIG/NET/04/IP/", "auth_key", "\x02"},
	{"/CONFIG/NET/04/IP/", "ip_address", "\x02"},
	{"/CONFIG/NET/04/IP/", "netmask", "\x02"},
	{"/CONFIG/NET/04/IP/", "default_route", "\x02"},
	{"/CONFIG/NET/04/IP/", "dns_flag", "\x01"},
	{"/CONFIG/NET/04/IP/", "primary_dns", "\x02"},
	{"/CONFIG/NET/04/IP/", "secondary_dns", "\x02"},
	{"/CONFIG/NET/04/APP/", "http_proxy_flag", "\x01"},
	{"/CONFIG/NET/04/APP/", "http_proxy_server", "\x02"},
	{"/CONFIG/NET/04/APP/", "http_proxy_port", "\x01"},
	{"/CONFIG/NET/05/COMMON/", "conf_flag", "\x01"},
	{"/CONFIG/NET/05/COMMON/", "conf_type", "\x01"},
	{"/CONFIG/NET/05/COMMON/", "conf_name", "\x02"},
	{"/CONFIG/NET/05/COMMON/", "conf_serial_no", "\x01"},
	{"/CONFIG/NET/05/COMMON/", "enable_auto_connect", "\x01"},
	{"/CONFIG/NET/05/COMMON/", "mtu", "\x01"},
	{"/CONFIG/NET/05/COMMON/", "device", "\x01"},
	{"/CONFIG/NET/05/COMMON/", "ether_mode", "\x01"},
	{"/CONFIG/NET/05/WIFI/", "ssid", "\x02"},
	{"/CONFIG/NET/05/WIFI/", "wifi_security", "\x01"},
	{"/CONFIG/NET/05/WIFI/", "wep_key", "\x02"},
	{"/CONFIG/NET/05/WIFI/", "wpa_key", "\x02"},
	{"/CONFIG/NET/05/IP/", "ip_config", "\x01"},
	{"/CONFIG/NET/05/IP/", "dhcp_hostname", "\x02"},
	{"/CONFIG/NET/05/IP/", "auth_name", "\x02"},
	{"/CONFIG/NET/05/IP/", "auth_key", "\x02"},
	{"/CONFIG/NET/05/IP/", "ip_address", "\x02"},
	{"/CONFIG/NET/05/IP/", "netmask", "\x02"},
	{"/CONFIG/NET/05/IP/", "default_route", "\x02"},
	{"/CONFIG/NET/05/IP/", "dns_flag", "\x01"},
	{"/CONFIG/NET/05/IP/", "primary_dns", "\x02"},
	{"/CONFIG/NET/05/IP/", "secondary_dns", "\x02"},
	{"/CONFIG/NET/05/APP/", "http_proxy_flag", "\x01"},
	{"/CONFIG/NET/05/APP/", "http_proxy_server", "\x02"},
	{"/CONFIG/NET/05/APP/", "http_proxy_port", "\x01"},
	{"/CONFIG/NET/06/COMMON/", "conf_flag", "\x01"},
	{"/CONFIG/NET/06/COMMON/", "conf_type", "\x01"},
	{"/CONFIG/NET/06/COMMON/", "conf_name", "\x02"},
	{"/CONFIG/NET/06/COMMON/", "conf_serial_no", "\x01"},
	{"/CONFIG/NET/06/COMMON/", "enable_auto_connect", "\x01"},
	{"/CONFIG/NET/06/COMMON/", "mtu", "\x01"},
	{"/CONFIG/NET/06/COMMON/", "device", "\x01"},
	{"/CONFIG/NET/06/COMMON/", "ether_mode", "\x01"},
	{"/CONFIG/NET/06/WIFI/", "ssid", "\x02"},
	{"/CONFIG/NET/06/WIFI/", "wifi_security", "\x01"},
	{"/CONFIG/NET/06/WIFI/", "wep_key", "\x02"},
	{"/CONFIG/NET/06/WIFI/", "wpa_key", "\x02"},
	{"/CONFIG/NET/06/IP/", "ip_config", "\x01"},
	{"/CONFIG/NET/06/IP/", "dhcp_hostname", "\x02"},
	{"/CONFIG/NET/06/IP/", "auth_name", "\x02"},
	{"/CONFIG/NET/06/IP/", "auth_key", "\x02"},
	{"/CONFIG/NET/06/IP/", "ip_address", "\x02"},
	{"/CONFIG/NET/06/IP/", "netmask", "\x02"},
	{"/CONFIG/NET/06/IP/", "default_route", "\x02"},
	{"/CONFIG/NET/06/IP/", "dns_flag", "\x01"},
	{"/CONFIG/NET/06/IP/", "primary_dns", "\x02"},
	{"/CONFIG/NET/06/IP/", "secondary_dns", "\x02"},
	{"/CONFIG/NET/06/APP/", "http_proxy_flag", "\x01"},
	{"/CONFIG/NET/06/APP/", "http_proxy_server", "\x02"},
	{"/CONFIG/NET/06/APP/", "http_proxy_port", "\x01"},
	{"/CONFIG/NET/07/COMMON/", "conf_flag", "\x01"},
	{"/CONFIG/NET/07/COMMON/", "conf_type", "\x01"},
	{"/CONFIG/NET/07/COMMON/", "conf_name", "\x02"},
	{"/CONFIG/NET/07/COMMON/", "conf_serial_no", "\x01"},
	{"/CONFIG/NET/07/COMMON/", "enable_auto_connect", "\x01"},
	{"/CONFIG/NET/07/COMMON/", "mtu", "\x01"},
	{"/CONFIG/NET/07/COMMON/", "device", "\x01"},
	{"/CONFIG/NET/07/COMMON/", "ether_mode", "\x01"},
	{"/CONFIG/NET/07/WIFI/", "ssid", "\x02"},
	{"/CONFIG/NET/07/WIFI/", "wifi_security", "\x01"},
	{"/CONFIG/NET/07/WIFI/", "wep_key", "\x02"},
	{"/CONFIG/NET/07/WIFI/", "wpa_key", "\x02"},
	{"/CONFIG/NET/07/IP/", "ip_config", "\x01"},
	{"/CONFIG/NET/07/IP/", "dhcp_hostname", "\x02"},
	{"/CONFIG/NET/07/IP/", "auth_name", "\x02"},
	{"/CONFIG/NET/07/IP/", "auth_key", "\x02"},
	{"/CONFIG/NET/07/IP/", "ip_address", "\x02"},
	{"/CONFIG/NET/07/IP/", "netmask", "\x02"},
	{"/CONFIG/NET/07/IP/", "default_route", "\x02"},
	{"/CONFIG/NET/07/IP/", "dns_flag", "\x01"},
	{"/CONFIG/NET/07/IP/", "primary_dns", "\x02"},
	{"/CONFIG/NET/07/IP/", "secondary_dns", "\x02"},
	{"/CONFIG/NET/07/APP/", "http_proxy_flag", "\x01"},
	{"/CONFIG/NET/07/APP/", "http_proxy_server", "\x02"},
	{"/CONFIG/NET/07/APP/", "http_proxy_port", "\x01"},
	{"/CONFIG/NET/08/COMMON/", "conf_flag", "\x01"},
	{"/CONFIG/NET/08/COMMON/", "conf_type", "\x01"},
	{"/CONFIG/NET/08/COMMON/", "conf_name", "\x02"},
	{"/CONFIG/NET/08/COMMON/", "conf_serial_no", "\x01"},
	{"/CONFIG/NET/08/COMMON/", "enable_auto_connect", "\x01"},
	{"/CONFIG/NET/08/COMMON/", "mtu", "\x01"},
	{"/CONFIG/NET/08/COMMON/", "device", "\x01"},
	{"/CONFIG/NET/08/COMMON/", "ether_mode", "\x01"},
	{"/CONFIG/NET/08/WIFI/", "ssid", "\x02"},
	{"/CONFIG/NET/08/WIFI/", "wifi_security", "\x01"},
	{"/CONFIG/NET/08/WIFI/", "wep_key", "\x02"},
	{"/CONFIG/NET/08/WIFI/", "wpa_key", "\x02"},
	{"/CONFIG/NET/08/IP/", "ip_config", "\x01"},
	{"/CONFIG/NET/08/IP/", "dhcp_hostname", "\x02"},
	{"/CONFIG/NET/08/IP/", "auth_name", "\x02"},
	{"/CONFIG/NET/08/IP/", "auth_key", "\x02"},
	{"/CONFIG/NET/08/IP/", "ip_address", "\x02"},
	{"/CONFIG/NET/08/IP/", "netmask", "\x02"},
	{"/CONFIG/NET/08/IP/", "default_route", "\x02"},
	{"/CONFIG/NET/08/IP/", "dns_flag", "\x01"},
	{"/CONFIG/NET/08/IP/", "primary_dns", "\x02"},
	{"/CONFIG/NET/08/IP/", "secondary_dns", "\x02"},
	{"/CONFIG/NET/08/APP/", "http_proxy_flag", "\x01"},
	{"/CONFIG/NET/08/APP/", "http_proxy_server", "\x02"},
	{"/CONFIG/NET/08/APP/", "http_proxy_port", "\x01"},
	{"/CONFIG/NET/09/COMMON/", "conf_flag", "\x01"},
	{"/CONFIG/NET/09/COMMON/", "conf_type", "\x01"},
	{"/CONFIG/NET/09/COMMON/", "conf_name", "\x02"},
	{"/CONFIG/NET/09/COMMON/", "conf_serial_no", "\x01"},
	{"/CONFIG/NET/09/COMMON/", "enable_auto_connect", "\x01"},
	{"/CONFIG/NET/09/COMMON/", "mtu", "\x01"},
	{"/CONFIG/NET/09/COMMON/", "device", "\x01"},
	{"/CONFIG/NET/09/COMMON/", "ether_mode", "\x01"},
	{"/CONFIG/NET/09/WIFI/", "ssid", "\x02"},
	{"/CONFIG/NET/09/WIFI/", "wifi_security", "\x01"},
	{"/CONFIG/NET/09/WIFI/", "wep_key", "\x02"},
	{"/CONFIG/NET/09/WIFI/", "wpa_key", "\x02"},
	{"/CONFIG/NET/09/IP/", "ip_config", "\x01"},
	{"/CONFIG/NET/09/IP/", "dhcp_hostname", "\x02"},
	{"/CONFIG/NET/09/IP/", "auth_name", "\x02"},
	{"/CONFIG/NET/09/IP/", "auth_key", "\x02"},
	{"/CONFIG/NET/09/IP/", "ip_address", "\x02"},
	{"/CONFIG/NET/09/IP/", "netmask", "\x02"},
	{"/CONFIG/NET/09/IP/", "default_route", "\x02"},
	{"/CONFIG/NET/09/IP/", "dns_flag", "\x01"},
	{"/CONFIG/NET/09/IP/", "primary_dns", "\x02"},
	{"/CONFIG/NET/09/IP/", "secondary_dns", "\x02"},
	{"/CONFIG/NET/09/APP/", "http_proxy_flag", "\x01"},
	{"/CONFIG/NET/09/APP/", "http_proxy_server", "\x02"},
	{"/CONFIG/NET/09/APP/", "http_proxy_port", "\x01"},
	{"/CONFIG/NET/10/COMMON/", "conf_flag", "\x01"},
	{"/CONFIG/NET/10/COMMON/", "conf_type", "\x01"},
	{"/CONFIG/NET/10/COMMON/", "conf_name", "\x02"},
	{"/CONFIG/NET/10/COMMON/", "conf_serial_no", "\x01"},
	{"/CONFIG/NET/10/COMMON/", "enable_auto_connect", "\x01"},
	{"/CONFIG/NET/10/COMMON/", "mtu", "\x01"},
	{"/CONFIG/NET/10/COMMON/", "device", "\x01"},
	{"/CONFIG/NET/10/COMMON/", "ether_mode", "\x01"},
	{"/CONFIG/NET/10/WIFI/", "ssid", "\x02"},
	{"/CONFIG/NET/10/WIFI/", "wifi_security", "\x01"},
	{"/CONFIG/NET/10/WIFI/", "wep_key", "\x02"},
	{"/CONFIG/NET/10/WIFI/", "wpa_key", "\x02"},
	{"/CONFIG/NET/10/IP/", "ip_config", "\x01"},
	{"/CONFIG/NET/10/IP/", "dhcp_hostname", "\x02"},
	{"/CONFIG/NET/10/IP/", "auth_name", "\x02"},
	{"/CONFIG/NET/10/IP/", "auth_key", "\x02"},
	{"/CONFIG/NET/10/IP/", "ip_address", "\x02"},
	{"/CONFIG/NET/10/IP/", "netmask", "\x02"},
	{"/CONFIG/NET/10/IP/", "default_route", "\x02"},
	{"/CONFIG/NET/10/IP/", "dns_flag", "\x01"},
	{"/CONFIG/NET/10/IP/", "primary_dns", "\x02"},
	{"/CONFIG/NET/10/IP/", "secondary_dns", "\x02"},
	{"/CONFIG/NET/10/APP/", "http_proxy_flag", "\x01"},
	{"/CONFIG/NET/10/APP/", "http_proxy_server", "\x02"},
	{"/CONFIG/NET/10/APP/", "http_proxy_port", "\x01"},
	{"/CONFIG/NET/ETH/COMMON/", "mtu", "\x01"},
	{"/CONFIG/NET/ETH/COMMON/", "config_done", "\x01"},
	{"/CONFIG/NET/ETH/IP/", "ip_config", "\x01"},
	{"/CONFIG/NET/ETH/IP/", "dhcp_hostname", "\x02"},
	{"/CONFIG/NET/ETH/IP/", "auth_name", "\x02"},
	{"/CONFIG/NET/ETH/IP/", "auth_key", "\x02"},
	{"/CONFIG/NET/ETH/IP/", "ip_address", "\x02"},
	{"/CONFIG/NET/ETH/IP/", "netmask", "\x02"},
	{"/CONFIG/NET/ETH/IP/", "default_route", "\x02"},
	{"/CONFIG/NET/ETH/IP/", "dns_flag", "\x01"},
	{"/CONFIG/NET/ETH/IP/", "primary_dns", "\x02"},
	{"/CONFIG/NET/ETH/IP/", "secondary_dns", "\x02"},
	{"/CONFIG/NET/ETH/APP/", "http_proxy_flag", "\x01"},
	{"/CONFIG/NET/ETH/APP/", "http_proxy_server", "\x02"},
	{"/CONFIG/NET/ETH/APP/", "http_proxy_port", "\x01"},
	{"/CONFIG/NP/", "enable_np", "\x01"},
	{"/CONFIG/NP/", "account_id", "\x03"},
	{"/CONFIG/NP/", "login_id", "\x02"},
	{"/CONFIG/NP/", "password", "\x02"},
	{"/CONFIG/NP/", "env", "\x02"},
	{"/CONFIG/NP/", "pc_store_front", "\x01"},
	{"/CONFIG/NP/", "debug", "\x01"},
	{"/CONFIG/NP/", "debug_ingame_commerce2", "\x01"},
	{"/CONFIG/NP/", "debug_upgradable", "\x01"},
	{"/CONFIG/NP/", "title_id", "\x02"},
	{"/CONFIG/NP/", "nav_only", "\x01"},
	{"/CONFIG/NP/", "np_ad_clock_diff", "\x01"},
	{"/CONFIG/NP/", "np_geo_filtering", "\x01"},
	{"/CONFIG/NP/", "download_confirmed", "\x01"},
	{"/CONFIG/NP/", "country", "\x02"},
	{"/CONFIG/NP/", "lang", "\x02"},
	{"/CONFIG/NP/", "yob", "\x01"},
	{"/CONFIG/NP/", "mob", "\x01"},
	{"/CONFIG/NP/", "dob", "\x01"},
	{"/CONFIG/NP/", "has_subaccount", "\x01"},
	{"/CONFIG/NP/", "current_account", "\x01"},
	{"/CONFIG/NP2/", "privacy_confirmation", "\x01"},
	{"/CONFIG/NP2/", "auto_download", "\x01"},
	{"/CONFIG/NP2/", "current_account2", "\x01"},
	{"/CONFIG/NP2/", "test_patch", "\x01"},
	{"/CONFIG/NP2/", "tpps_proxy_server", "\x02"},
	{"/CONFIG/NP2/", "tpps_proxy_port", "\x01"},
	{"/CONFIG/NP2/", "tpps_proxy_user_name", "\x02"},
	{"/CONFIG/NP2/", "tpps_proxy_password", "\x02"},
	{"/CONFIG/NP2/", "tpps_proxy_flag", "\x01"},
	{"/CONFIG/NP2/", "debug_drm_loose_bind", "\x01"},
	{"/CONFIG/NP2/", "trophy_setup_dialog_debug", "\x01"},
	{"/CONFIG/NP2/", "fake_plus", "\x01"},
	{"/CONFIG/NP2/", "fake_ratelimit", "\x01"},
	{"/CONFIG/NP2/", "ignore_titleid", "\x01"},
	{"/CONFIG/NP2/AUTOUPDATE/", "enable", "\x01"},
	{"/CONFIG/NP2/AUTOUPDATE/", "application", "\x01"},
	{"/CONFIG/NP2/AUTOUPDATE/", "system", "\x01"},
	{"/CONFIG/NP2/AUTOUPDATE/", "trophy", "\x01"},
	{"/CONFIG/NP2/AUTOUPDATE/", "save_data", "\x01"},
	{"/CONFIG/NP2/PSNMSG/", "fetch_interval", "\x01"},
	{"/CONFIG/NP2/FACEBOOK/", "account", "\x02"},
	{"/CONFIG/NP2/FACEBOOK/", "session_key", "\x02"},
	{"/CONFIG/NP2/FACEBOOK/", "session_secret", "\x02"},
	{"/CONFIG/NP2/FACEBOOK/", "uid", "\x02"},
	{"/CONFIG/NP2/FACEBOOK/", "access_token", "\x02"},
	{"/CONFIG/NP2/FACEBOOK/", "share_trophy", "\x01"},
	{"/CONFIG/NP2/FACEBOOK/", "share_purchase", "\x01"},
	{"/CONFIG/NP2/FACEBOOK/", "share_rating", "\x01"},
	{"/CONFIG/NP2/FACEBOOK/", "game_integrations", "\x01"},
	{"/CONFIG/NP2/TWITTER/", "access_token", "\x02"},
	{"/CONFIG/NP2/TWITTER/", "access_token_secret", "\x02"},
	{"/CONFIG/NP2/TELEPORT/", "passcode_server", "\x02"},
	{"/CONFIG/NP2/TELEPORT/", "wol_target_mac_address", "\x03"},
	{"/CONFIG/NP2/TELEPORT/", "target_name", "\x02"},
	{"/CONFIG/NP2/TELEPORT/", "initial_target", "\x01"},
	{"/CONFIG/NP2/TELEPORT/", "passcode_client", "\x02"},
	{"/CONFIG/NP2/TELEPORT/", "enable_media_transfer", "\x01"},
	{"/CONFIG/NP_MULTI/", "accountname_00", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_01", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_02", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_03", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_04", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_05", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_06", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_07", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_08", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_09", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_10", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_11", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_12", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_13", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_14", "\x02"},
	{"/CONFIG/NP_MULTI/", "accountname_15", "\x02"},
	{"/CONFIG/LOCATION/", "enable_service", "\x01"},
	{"/CONFIG/LOCATION/", "enable_parental", "\x01"},
	{"/CONFIG/LOCATION/", "xps_config", "\x03"},
	{"/CONFIG/LOCATION/", "last_latitude", "\x02"},
	{"/CONFIG/LOCATION/", "last_longitude", "\x02"},
	{"/CONFIG/LOCATION/", "enable_log", "\x01"},
	{"/CONFIG/LOCATION/", "update_counter", "\x01"},
	{"/CONFIG/LOCATION/", "enable_locale", "\x01"},
	{"/CONFIG/LOCATION/", "enable_locale_last", "\x01"},
	{"/CONFIG/LOCATION/", "permit_age", "\x01"},
	{"/CONFIG/LOCATION/", "age_permit_state", "\x01"},
	{"/CONFIG/LOCATION/", "last_update_counter", "\x01"},
	{"/CONFIG/LOCATION/", "emulation_mode", "\x01"},
	{"/CONFIG/LOCATION/", "debug_permission", "\x01"},
	{"/CONFIG/LOCATION/", "debug_permission_status", "\x01"},
	{"/CONFIG/LOCATION/", "make_ap_invisible", "\x01"},
	{"/CONFIG/EMAIL/", "fetch_interval", "\x01"},
	{"/CONFIG/EMAIL/", "enable_auto_start", "\x01"},
	{"/CONFIG/TEL/", "use_debug_settings", "\x01"},
	{"/CONFIG/TEL/", "is_com_exist", "\x01"},
	{"/CONFIG/TEL/", "target_operator", "\x01"},
	{"/CONFIG/TEL/", "product_target_operator", "\x01"},
	{"/CONFIG/TEL/", "enable_wwan", "\x01"},
	{"/CONFIG/TEL/", "apn_name", "\x02"},
	{"/CONFIG/TEL/", "apn_user_id", "\x02"},
	{"/CONFIG/TEL/", "apn_password", "\x02"},
	{"/CONFIG/TEL/", "is_apn_init", "\x01"},
	{"/CONFIG/TEL/", "sim_unique_id", "\x02"},
	{"/CONFIG/TEL/", "billing_plan", "\x01"},
	{"/CONFIG/TEL/", "mcc", "\x01"},
	{"/CONFIG/TEL/", "mnc", "\x01"},
	{"/CONFIG/TEL/", "rat", "\x01"},
	{"/CONFIG/TEL/", "network_selection", "\x01"},
	{"/CONFIG/TEL/", "enable_data_roaming", "\x01"},
	{"/CONFIG/TEL/", "antenna_disp_type", "\x01"},
	{"/CONFIG/TEL/", "operator_site", "\x02"},
	{"/CONFIG/TEL/", "show_operator_info", "\x01"},
	{"/CONFIG/TEL/", "usb_setting", "\x01"},
	{"/CONFIG/TEL/", "forbidden_phone0", "\x01"},
	{"/CONFIG/TEL/", "dbg_log_tel", "\x01"},
	{"/CONFIG/TEL/", "dbg_log_bbmc", "\x01"},
	{"/CONFIG/TEL/", "dbg_log_net", "\x01"},
	{"/CONFIG/BROWSER/", "web_security_status", "\x01"},
	{"/CONFIG/BROWSER/ADDIN/TRENDMICRO/", "tm_service", "\x01"},
	{"/CONFIG/BROWSER/ADDIN/TRENDMICRO/", "tm_ec_ttl", "\x01"},
	{"/CONFIG/BROWSER/ADDIN/TRENDMICRO/", "tm_ec_ttl_update_time", "\x03"},
	{"/CONFIG/BROWSER/ADDIN/TRENDMICRO/", "tm_service_sub_status", "\x01"},
	{"/CONFIG/BROWSER/DEBUG/", "force_create_webcore_mini", "\x01"},
	{"/CONFIG/BROWSER/DEBUG/", "enable_fgdl", "\x01"},
	{"/CONFIG/BROWSER/DEBUG/", "net_dbg_config", "\x01"},
	{"/CONFIG/THEME/", "wallpaper", "\x01"},
	{"/CONFIG/THEME/", "wallpaper_tex_w", "\x01"},
	{"/CONFIG/THEME/", "wallpaper_tex_h", "\x01"},
	{"/CONFIG/THEME/", "current_theme", "\x02"},
	{"/CONFIG/THEME/", "enable_store_link", "\x01"},
	{"/CONFIG/USB/", "usb_charge_enable", "\x01"},
	{"/CONFIG/PHOTO/", "debug_screenshot", "\x01"},
	{"/CONFIG/PHOTO/", "debug_screenshot_format", "\x01"},
	{"/CONFIG/MUSIC/MUSIC_APP/", "repeat_mode", "\x01"},
	{"/CONFIG/MUSIC/MUSIC_APP/", "shuffle_mode", "\x01"},
	{"/CONFIG/MUSIC/MUSIC_APP/", "audio_normalizer", "\x01"},
	{"/CONFIG/MUSIC/MUSIC_APP/", "audio_equalize_type", "\x01"},
	{"/CONFIG/MUSIC/MUSIC_APP/", "audio_balance", "\x01"},
	{"/CONFIG/MUSIC/MUSIC_APP/", "impose_audio_balance", "\x01"},
	{"/CONFIG/VIDEO/", "debug_videoplayer", "\x01"},
	{"/CONFIG/GAME/", "fake_free_space", "\x01"},
	{"/CONFIG/GAME/", "fake_free_space_quota", "\x01"},
	{"/CONFIG/GAME/", "fake_no_memory_card", "\x01"},
	{"/CONFIG/GAME/", "fake_contents_max", "\x01"},
	{"/CONFIG/GAME/", "init_safememory", "\x01"},
	{"/CONFIG/GAME/", "fake_savedata_owner", "\x01"},
	{"/CONFIG/GAME/", "show_debug_info", "\x01"},
	{"/CONFIG/GAME/", "fake_sdslot_broken", "\x01"},
	{"/CONFIG/PSPEMU/", "psp_first_boot", "\x01"},
	{"/CONFIG/PSPEMU/", "ps1_first_boot", "\x01"},
	{"/CONFIG/PSPEMU/", "pocketstation_first_boot", "\x01"},
	{"/CONFIG/PSPEMU/", "emu_list_flag", "\x01"},
	{"/CONFIG/PSPEMU/", "enable_list", "\x01"},
	{"/CONFIG/PSPEMU/SETTINGS/", "disp_filter", "\x01"},
	{"/CONFIG/PSPEMU/SETTINGS/", "camera_direction", "\x01"},
	{"/CONFIG/PSPEMU/SETTINGS/", "delete_contents", "\x01"},
	{"/CONFIG/PSPEMU/SETTINGS/", "ra_up", "\x01"},
	{"/CONFIG/PSPEMU/SETTINGS/", "ra_down", "\x01"},
	{"/CONFIG/PSPEMU/SETTINGS/", "ra_left", "\x01"},
	{"/CONFIG/PSPEMU/SETTINGS/", "ra_right", "\x01"},
	{"/CONFIG/PSPEMU/SETTINGS/", "color_space", "\x01"},
	{"/CONFIG/PSPEMU/SETTINGS/", "screen_left_up", "\x01"},
	{"/CONFIG/PSPEMU/SETTINGS/", "screen_right_up", "\x01"},
	{"/CONFIG/PSPEMU/SETTINGS/", "screen_left_down", "\x01"},
	{"/CONFIG/PSPEMU/SETTINGS/", "screen_right_down", "\x01"},
	{"/CONFIG/PSM/", "revocation_check_req", "\x01"},
	{"/CONFIG/COREDUMP/", "dump_level", "\x01"},
	{"/CONFIG/COREDUMP/", "dest_hostpath", "\x02"},
	{"/CONFIG/COREDUMP/", "force_dump_on_devmode", "\x01"},
	{"/CONFIG/COREDUMP/", "always_encrypt_dump", "\x01"},
	{"/CONFIG/COREDUMP/CRASHREPORT/", "keep_corefiles", "\x01"},
	{"/CONFIG/COREDUMP/UPLOADER/", "enable_flag", "\x01"},
	{"/CONFIG/COREDUMP/UPLOADER/", "auto_flag", "\x01"},
	{"/CONFIG/COREDUMP/UPLOADER/", "url", "\x02"},
	{"/CONFIG/MTP/", "interface_type", "\x01"},
	{"/CONFIG/MTP/NET/", "num_hosts", "\x01"},
	{"/CONFIG/MTP/NET/00/", "config_flag", "\x01"},
	{"/CONFIG/MTP/NET/00/", "assigned", "\x01"},
	{"/CONFIG/MTP/NET/00/", "host_id", "\x03"},
	{"/CONFIG/MTP/NET/00/", "host_name", "\x02"},
	{"/CONFIG/MTP/NET/00/", "host_type", "\x01"},
	{"/CONFIG/MTP/NET/00/", "last_connected_time", "\x03"},
	{"/CONFIG/MTP/NET2/", "num_hosts", "\x01"},
	{"/CONFIG/MTP/NET2/00/", "config_flag", "\x01"},
	{"/CONFIG/MTP/NET2/00/", "assigned", "\x01"},
	{"/CONFIG/MTP/NET2/00/", "host_id", "\x03"},
	{"/CONFIG/MTP/NET2/00/", "host_name", "\x02"},
	{"/CONFIG/MTP/NET2/00/", "host_type", "\x01"},
	{"/CONFIG/MTP/NET2/00/", "last_connected_time", "\x03"},
	{"/CONFIG/MTP/NET2/00/", "mac_address", "\x03"},
	{"/CONFIG/MTP/NET3/", "num_hosts", "\x01"},
	{"/CONFIG/MTP/NET3/00/", "config_flag", "\x01"},
	{"/CONFIG/MTP/NET3/00/", "assigned", "\x01"},
	{"/CONFIG/MTP/NET3/00/", "host_id", "\x01"},
	{"/CONFIG/MTP/NET3/00/", "host_name", "\x01"},
	{"/CONFIG/MTP/NET3/00/", "host_type", "\x01"},
	{"/CONFIG/MTP/NET3/00/", "last_connected_time", "\x01"},
	{"/CONFIG/MTP/NET3/00/", "mac_address", "\x03"},
	{"/CONFIG/PS4LINK/", "counter", "\x01"},
	{"/CONFIG/PS4LINK/", "keys", "\x03"},
	{"/CONFIG/VIDEOSERVICE/MARLINIPTV/", "dirty_flag", "\x01"},
	{"/CONFIG/VIDEOSERVICE/MARLINIPTV/01/", "device_key", "\x03"},
	{"/CONFIG/VIDEOSERVICE/MARLINIPTV/02/", "device_key", "\x03"},
	{"/CONFIG/VIDEOSERVICE/MARLINIPTV/03/", "device_key", "\x03"},
	{"/CONFIG/SPECIFIC/", "contents_dl_url", "\x02"},
	{"/CONFIG/SPECIFIC/", "idu_mode", "\x01"},
	{"/CONFIG/SPECIFIC/", "idu_video_latency", "\x01"},
	{"/CONFIG/SPECIFIC/", "idu_ps4link", "\x01"},
	{"/CONFIG/SPECIFIC/", "backup_key", "\x01"},
	{"/CONFIG/PSNOW/", "app_cached_url", "\x02"},
	{"/DEVENV/HOST/", "host_internal", "\x01"},
	{"/DEVENV/HOST/", "devkitname", "\x02"},
	{"/DEVENV/HOST/", "current_ip_address", "\x02"},
	{"/DEVENV/HOST/", "ui_serial", "\x01"},
	{"/DEVENV/HOST/", "ev_serial", "\x01"},
	{"/DEVENV/TOOL/", "gpi_switch", "\x01"},
	{"/DEVENV/TOOL/", "region_masquerade", "\x01"},
	{"/DEVENV/TOOL/", "hdmi_video_mode", "\x01"},
	{"/DEVENV/TOOL/", "hdmi_color_range", "\x01"},
	{"/DEVENV/TOOL/", "hdmi_audio_mode", "\x01"},
	{"/DEVENV/TOOL/", "slow_card_mode", "\x01"},
	{"/DEVENV/TOOL/", "machine_type", "\x01"},
	{"/DEVENV/TOOL/", "use_default_lib", "\x01"},
	{"/DEVENV/TOOL/", "vsh_uses_gxmdbg", "\x01"},
	{"/DEVENV/TOOL/", "game_uses_gxmdbg", "\x01"},
	{"/DEVENV/TOOL/", "webcore_plugin_host", "\x01"},
	{"/DEVENV/TOOL/", "prx_debug", "\x01"},
	{"/DEVENV/TOOL/", "enable_sharedfb_timeout", "\x01"},
	{"/DEVENV/TOOL/", "enable_shell_watch_dog", "\x01"},
	{"/DEVENV/TOOL/", "error_masquerade", "\x01"},
	{"/DEVENV/TOOL/", "error_countdown", "\x01"},
	{"/DEVENV/TOOL/", "event_log", "\x03"}
};

void initSceAppUtil()
{
	// Init SceAppUtil
	SceAppUtilInitParam init_param;
	SceAppUtilBootParam boot_param;
	memset(&init_param, 0, sizeof(SceAppUtilInitParam));
	memset(&boot_param, 0, sizeof(SceAppUtilBootParam));
	sceAppUtilInit(&init_param, &boot_param);

	// Set common dialog config
	SceCommonDialogConfigParam config;
	sceCommonDialogConfigParamInit(&config);
	sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_LANG, (int *)&config.language);
	sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_ENTER_BUTTON, (int *)&config.enterButtonAssign);
	sceCommonDialogSetConfigParam(&config);
}

void getButtons(int *holdButtons, int *pressedButtons)
{
	static int hold_n = 0;
	static int old_buttons, current_buttons, pressed_buttons, hold_buttons;
	SceCtrlData pad;

	memset(&pad, 0, sizeof(SceCtrlData));
	sceCtrlPeekBufferPositive(0, &pad, 1);

	if (pad.ly < ANALOG_CENTER - ANALOG_THRESHOLD)
		pad.buttons |= SCE_CTRL_LEFT_ANALOG_UP;
	else if (pad.ly > ANALOG_CENTER + ANALOG_THRESHOLD)
		pad.buttons |= SCE_CTRL_LEFT_ANALOG_DOWN;

	if (pad.lx < ANALOG_CENTER - ANALOG_THRESHOLD)
		pad.buttons |= SCE_CTRL_LEFT_ANALOG_LEFT;
	else if (pad.lx > ANALOG_CENTER + ANALOG_THRESHOLD)
		pad.buttons |= SCE_CTRL_LEFT_ANALOG_RIGHT;

	if (pad.ry < ANALOG_CENTER - ANALOG_THRESHOLD)
		pad.buttons |= SCE_CTRL_RIGHT_ANALOG_UP;
	else if (pad.ry > ANALOG_CENTER + ANALOG_THRESHOLD)
		pad.buttons |= SCE_CTRL_RIGHT_ANALOG_DOWN;

	if (pad.rx < ANALOG_CENTER - ANALOG_THRESHOLD)
		pad.buttons |= SCE_CTRL_RIGHT_ANALOG_LEFT;
	else if (pad.rx > ANALOG_CENTER + ANALOG_THRESHOLD)
		pad.buttons |= SCE_CTRL_RIGHT_ANALOG_RIGHT;

	current_buttons = pad.buttons;
	pressed_buttons = current_buttons & ~old_buttons;
	hold_buttons = pressed_buttons;

	if (old_buttons == current_buttons)
	{
		hold_n++;
		if (hold_n >= 10)
		{
			hold_buttons = current_buttons;
			hold_n = 6;
		}
	}
	else
	{
		hold_n = 0;
		old_buttons = current_buttons;
	}
	
	*holdButtons = hold_buttons;
	*pressedButtons = pressed_buttons;
}

int startsWith(const char *str1, const char *str2)
{
    return strncmp(str1, str2, strlen(str1)) == 0;
}

void initializeRegistryDirectory(RegistryDirectory *root)
{
	RegistryDirectory *curDir = root;
	int i = 0;

	while(i < SIZE)
	{
		//printf("%d\n", i);
		if(startsWith(curDir->name, regData[i][0]) && strcmp(curDir->name, regData[i][0]) != 0)
		{
			//Child Node
			RegistryDirectory *childDir = (RegistryDirectory*)malloc(sizeof(RegistryDirectory));
			char *p;
			
			//Initialize child
			childDir->numKeys = 0;
			childDir->numSubDirs = 0;
			childDir->parent = curDir;
			childDir->keys = NULL;
			childDir->subdirs = NULL;
			
			//Set child name
			p = strstr(regData[i][0] + strlen(curDir->name), "/");
			childDir->name = (char*)malloc(p - regData[i][0] + 2);
			memset(childDir->name, 0, p - regData[i][0] + 2);
			strncpy(childDir->name, regData[i][0], p - regData[i][0] + 1);
			
			//Insert child into parent
			curDir->numSubDirs++;
			curDir->subdirs = (RegistryDirectory**)realloc(curDir->subdirs, sizeof(RegistryDirectory*) * curDir->numSubDirs);
			curDir->subdirs[curDir->numSubDirs - 1] = childDir;
			
			//Next
			curDir = childDir;
		}
		else if(strcmp(curDir->name, regData[i][0]) == 0)
		{
			//Set key
			RegistryKey *key = (RegistryKey*)malloc(sizeof(RegistryKey));
			
			//Initialize Key
			key->keyType = regData[i][2][0];
			key->keyName = (char*)malloc(strlen(regData[i][1]) + 1);
			strncpy(key->keyName, regData[i][1], strlen(regData[i][1]) + 1);
			
			//Insert into current dir
			curDir->numKeys++;
			curDir->keys = (RegistryKey**)realloc(curDir->keys, sizeof(RegistryKey*) * curDir->numKeys);
			curDir->keys[curDir->numKeys - 1] = key;
			
			i++;
		}
		else
			curDir = curDir->parent;
		//curDir
	}
}

void freeRegistryDirectoryTree(RegistryDirectory *dir)
{
	int i;
	
	//Free children
	for(i = 0; i < dir->numSubDirs; i++)
	{
		freeRegistryDirectoryTree(dir->subdirs[i]);
	}
	
	//Free current
	for(i = 0; i < dir->numKeys; i++)
	{
		free(dir->keys[i]->keyName);
		free(dir->keys[i]);
	}
	
	if(strcmp(dir->name, "/")) //Don't free root
	{
		free(dir->name);
		free(dir->subdirs);
		free(dir->keys);
		free(dir);
	}
}

void printRegistryDirectoryTree(RegistryDirectory *dir, int depth)
{
	int i, j;
	
	if(!dir)
		return;
	
	for(j = 0; j < depth; i++)
		printf("    ");
		
	if(dir->parent)
		printf("%s\n", dir->name + strlen(dir->parent->name));
	else
		printf("%s\n", dir->name);
	
	for(i = 0; i < dir->numSubDirs; i++)
	{
		printRegistryDirectoryTree(dir->subdirs[i], depth+1);
	}
	
	for(i = 0; i < dir->numKeys; i++)
	{
		for(j = 0; j < depth + 1; j++)
			printf("    ");
			
		printf("%s\n", dir->keys[i]->keyName);
	}
}

void drawScrollBar(int pos, int n)
{
	if (n > MAX_POSITION)
	{
		vita2d_draw_rectangle(SCROLL_BAR_X, 4.0f * FONT_Y_SPACE, SCROLL_BAR_WIDTH, MAX_ENTRIES * FONT_Y_SPACE, GRAY);

		float y = (4.0f * FONT_Y_SPACE) + ((pos * FONT_Y_SPACE) / (n * FONT_Y_SPACE)) * (MAX_ENTRIES * FONT_Y_SPACE);
		float height = ((MAX_POSITION * FONT_Y_SPACE) / (n * FONT_Y_SPACE)) * (MAX_ENTRIES * FONT_Y_SPACE);

		vita2d_draw_rectangle(0, MIN(y, ((4.0f * FONT_Y_SPACE) + MAX_ENTRIES * FONT_Y_SPACE - height)), SCROLL_BAR_WIDTH, MAX(height, SCROLL_BAR_MIN_HEIGHT), AZURE);
	}
}

int regMgrGetKeyInt(char *path, char *keyName)
{
	int val = -1, ret = 0;
	
	ret = sceRegMgrGetKeyInt(path, keyName, &val);
	
	if(ret < 0)
		return ret;
	else
		return val;
}

/*
	Errors from SceMgrGetKey
	0x800D000E - Not supported on this device
	0x800D000A - Path doesn't exist
	0x800D0014 - Key doesn't exist
	0x800D0015 - ?
	0x800D0017 - Something not found ex (/CONFIG/US_ENGLISH/input_type: 0x800D0017)
	0x800D000B - Wrong data type
	0x80022005 - You suck at returning my strings (No size provided)
*/

int main()
{
	curPosList[0] = 1;
	topList[0] = 0;
	int curSize = 0, ret = 0, imeStatus = 0, keyIndex = 0;
	int holdButtons = 0, pressedButtons = 0;
	int writeRet = 0;
	char buf[2048];
	vita2d_pgf *pgf;
	RegistryDirectory root =
	{
		"/",
		NULL,
		0,
		0,
		NULL,
		NULL
	};
	RegistryDirectory *curDir = &root;
	RegistryDirectory *writeDir = NULL;

	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
	initSceAppUtil();
	initializeRegistryDirectory(&root);
	
	vita2d_init();
	pgf = vita2d_load_default_pgf();
	
	while (1)
	{
		vita2d_start_drawing();
		vita2d_clear_screen();
		
		vita2d_pgf_draw_text(pgf, 20.0f, FONT_Y_SPACE, VIOLET, FONT_SIZE, "RegistryEditor");
		vita2d_pgf_draw_text(pgf, 20.0f, 2.0f * FONT_Y_SPACE, LITEGRAY, FONT_SIZE, curDir->name);
		
		imeStatus = updateImeDialog();
		
		if(imeStatus == IME_DIALOG_RESULT_FINISHED && writeDir)
		{
			char *output = (char *)getImeDialogInputTextUTF8();
			
			if(writeDir->keys[keyIndex]->keyType == KEY_TYPE_INT)
				writeRet = sceRegMgrSetKeyInt(writeDir->name, writeDir->keys[keyIndex]->keyName, atoi(output));
			else if(writeDir->keys[keyIndex]->keyType == KEY_TYPE_STR)
				writeRet = sceRegMgrSetKeyStr(writeDir->name, writeDir->keys[keyIndex]->keyName, output, strlen(output)+1);
			
			writeDir = NULL;
			keyIndex = 0;
		}
		
		curSize = curDir->numSubDirs + curDir->numKeys + 1;
		drawScrollBar(topList[posInd], curSize);
		
		if(curDir->parent && !topList[posInd])
			vita2d_pgf_draw_text(pgf, 20.0f, 4.0f * FONT_Y_SPACE, (!curPosList[posInd]) ? GREEN : CYAN, FONT_SIZE, "..");
		
		for(int i = topList[posInd]; i < curDir->numSubDirs && (i - topList[posInd]) < MAX_POSITION; i++)
		{
			uint32_t color = CYAN;
			float y = (5.0f * FONT_Y_SPACE) + ((i - topList[posInd]) * FONT_Y_SPACE);
			
			if(i == curPosList[posInd] - 1)
				color = GREEN;
			
			vita2d_pgf_draw_text(pgf, 20.0f, y, color, FONT_SIZE, curDir->subdirs[i]->name + strlen(curDir->name));
		}
		
		for(int i = (topList[posInd] < curDir->numSubDirs) ? 0 : topList[posInd] - curDir->numSubDirs; i < curDir->numKeys && (i - (topList[posInd] - curDir->numSubDirs)) < MAX_POSITION; i++)
		{
			uint32_t color = WHITE;
			float y = ((5.0f + curDir->numSubDirs) * FONT_Y_SPACE) + ((i - topList[posInd]) * FONT_Y_SPACE);
			
			if(curDir->keys[i]->keyType == KEY_TYPE_BIN)
				color = RED;
			if(i == curPosList[posInd] - 1 - curDir->numSubDirs)
				color = GREEN;
			
			if(curDir->keys[i]->keyType == KEY_TYPE_INT)
			{
				ret = regMgrGetKeyInt(curDir->name, curDir->keys[i]->keyName);
				
				if(ret == 0x800D000E)
					vita2d_pgf_draw_textf(pgf, 20.0f, y, color, FONT_SIZE, "%s: Not supported on this device", curDir->keys[i]->keyName);
				else
					vita2d_pgf_draw_textf(pgf, 20.0f, y, color, FONT_SIZE, (ret < 0) ? "%s: Error %08X" : "%s: %d", curDir->keys[i]->keyName, ret);
			}
			else if(curDir->keys[i]->keyType == KEY_TYPE_STR)
			{
				memset(buf, 0, 2048);
				ret = sceRegMgrGetKeyStr(curDir->name, curDir->keys[i]->keyName, buf, 2048);
				
				if(ret < 0)
				{
					if(ret == 0x800D000E)
						vita2d_pgf_draw_textf(pgf, 20.0f, y, color, FONT_SIZE, "%s: Not supported on this device", curDir->keys[i]->keyName);
					else
						vita2d_pgf_draw_textf(pgf, 20.0f, y, color, FONT_SIZE, "%s: Error %08X", curDir->keys[i]->keyName, ret);
				}
				else
					vita2d_pgf_draw_textf(pgf, 20.0f, y, color, FONT_SIZE, "%s: %s", curDir->keys[i]->keyName, buf);
			}
			else if(curDir->keys[i]->keyType == KEY_TYPE_BIN)
			{
				memset(buf, 0, 2048);
				ret = sceRegMgrGetKeyBin(curDir->name, curDir->keys[i]->keyName, buf, 2048);
				
				if(ret < 0)
				{
					if(ret == 0x800D000E)
						vita2d_pgf_draw_textf(pgf, 20.0f, y, color, FONT_SIZE, "%s: Not supported on this device", curDir->keys[i]->keyName);
					else
						vita2d_pgf_draw_textf(pgf, 20.0f, y, color, FONT_SIZE, "%s: Error %08X", curDir->keys[i]->keyName, ret);
				}
				else
				{
					vita2d_pgf_draw_textf(pgf, 20.0f, y, color, FONT_SIZE, "%s: Bin not yet supported", curDir->keys[i]->keyName);
				}
			}
			
			else
				vita2d_pgf_draw_text(pgf, 20.0f, y, color, FONT_SIZE, curDir->keys[i]->keyName);
		}

		getButtons(&holdButtons, &pressedButtons);
		
		if(pressedButtons & SCE_CTRL_START)
			break;
		
		if(holdButtons & SCE_CTRL_DOWN || holdButtons & SCE_CTRL_LEFT_ANALOG_DOWN)
		{			
			curPosList[posInd] = (curPosList[posInd] + 1) % curSize;
			
			if(curPosList[posInd] - topList[posInd] >= MAX_POSITION && curSize > MAX_POSITION && topList[posInd] < (curSize - MAX_POSITION - 1))
				topList[posInd]++;
			else if(curPosList[posInd] == 0 && curSize > MAX_POSITION)
				topList[posInd] = 0;
		}
		else if(holdButtons & SCE_CTRL_UP || holdButtons & SCE_CTRL_LEFT_ANALOG_UP)
		{
			if(--curPosList[posInd] < 0)
			{
				curPosList[posInd] = curSize - 1;
				
				if(curSize > MAX_POSITION)
				topList[posInd] = curSize - MAX_POSITION - 1;
			}
			
			if(curPosList[posInd] <= topList[posInd] && topList[posInd] && curSize > MAX_POSITION)
				topList[posInd]--;
		}
		
		if(pressedButtons & SCE_CTRL_CROSS)
		{
			if(curPosList[posInd] == 0)
			{
				if(curDir->parent) {
					posInd--;
					curDir = curDir->parent;
				}
				
				curPosList[posInd] = 0;
				topList[posInd] = 0;
			}
			else if(curPosList[posInd]- 1 < curDir->numSubDirs && curDir->numSubDirs > 0)
			{
				curDir = curDir->subdirs[curPosList[posInd] - 1];

				posInd++;
				curPosList[posInd] = 0;
				topList[posInd] = 0;
			}
			else
			{
				ret = -1;
				memset(buf, 0, 2048);
				
				if(curDir->keys[curPosList[posInd] - 1 - curDir->numSubDirs]->keyType == KEY_TYPE_INT)
				{
					ret = regMgrGetKeyInt(curDir->name, curDir->keys[curPosList[posInd] - 1 - curDir->numSubDirs]->keyName);
					sprintf(buf, "%d", ret);
				}
				else if(curDir->keys[curPosList[posInd] - 1 - curDir->numSubDirs]->keyType == KEY_TYPE_STR)
					ret = sceRegMgrGetKeyStr(curDir->name, curDir->keys[curPosList[posInd] - 1 - curDir->numSubDirs]->keyName, buf, 2048);
				//else if(curDir->keys[curPos - 1 - curDir->numSubDirs]->keyType == KEY_TYPE_BIN)
					//ret = sceRegMgrGetKeyBin(curDir->name, curDir->keys[curPos - 1 - curDir->numSubDirs]->keyName, buf, 2048);
				
				if(ret >= 0)
				{
					initImeDialog(curDir->keys[curPosList[posInd] - 1 - curDir->numSubDirs]->keyName, buf, 2048);
					writeDir = curDir;
					keyIndex = curPosList[posInd] - 1 - curDir->numSubDirs;
				}
				
			}
		}
		else if(pressedButtons & SCE_CTRL_CIRCLE && curDir->parent)
		{
			curDir = curDir->parent;
			posInd--;
		}
		
		if(writeRet < 0)
			vita2d_pgf_draw_textf(pgf, 20.0f, (23.0f * FONT_Y_SPACE), RED, FONT_SIZE, "Error writing to key: 0x%08X", writeRet);
		
		vita2d_end_drawing();
		vita2d_common_dialog_update();
		vita2d_swap_buffers();
		sceDisplayWaitVblankStart();
	}

	vita2d_fini();
	vita2d_free_pgf(pgf);
	freeRegistryDirectoryTree(&root);

	sceKernelExitProcess(0);
	return 0;
}
