#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint ;
typedef  void* u8 ;
typedef  void* u16 ;
struct TYPE_4__ {int SsidLength; int /*<<< orphan*/  Ssid; } ;
struct registry_priv {void* notch_filter; int /*<<< orphan*/  if2name; int /*<<< orphan*/  ifname; int /*<<< orphan*/  mac_phy_mode; void* hw_wps_pbc; void* antdiv_cfg; void* bAcceptAddbaReq; void* channel_plan; void* special_rf_path; void* wifi_spec; void* low_power; void* rf_config; void* lowrate_two_xmit; void* uapsd_acvo_en; void* uapsd_acvi_en; void* uapsd_acbe_en; void* uapsd_acbk_en; void* uapsd_max_sp; void* uapsd_enable; void* wmm_enable; void* acm_method; void* software_decrypt; void* software_encrypt; void* mp_mode; void* ack_policy; void* busy_thresh; void* short_retry_lmt; void* long_retry_lmt; void* radio_enable; void* ips_mode; void* power_mgnt; void* soft_ap; void* adhoc_tx_pwr; void* scan_mode; void* preamble; void* frag_thresh; void* rts_thresh; void* vcs_type; void* vrtl_carrier_sense; void* wireless_mode; void* channel; TYPE_1__ ssid; void* network_mode; void* lbkmode; void* rfintfs; void* chip_version; } ;
typedef  int /*<<< orphan*/  _nic_hdl ;
struct TYPE_5__ {struct registry_priv registrypriv; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_memcpy (int /*<<< orphan*/ ,char*,int) ; 
 char* if2name ; 
 char* ifname ; 
 scalar_t__ rtw_AcceptAddbaReq ; 
 scalar_t__ rtw_ack_policy ; 
 scalar_t__ rtw_acm_method ; 
 scalar_t__ rtw_adhoc_tx_pwr ; 
 scalar_t__ rtw_antdiv_cfg ; 
 scalar_t__ rtw_busy_thresh ; 
 scalar_t__ rtw_channel ; 
 scalar_t__ rtw_channel_plan ; 
 scalar_t__ rtw_chip_version ; 
 scalar_t__ rtw_frag_thresh ; 
 scalar_t__ rtw_hw_wps_pbc ; 
 scalar_t__ rtw_ips_mode ; 
 scalar_t__ rtw_lbkmode ; 
 scalar_t__ rtw_long_retry_lmt ; 
 scalar_t__ rtw_low_power ; 
 scalar_t__ rtw_lowrate_two_xmit ; 
 int /*<<< orphan*/  rtw_mac_phy_mode ; 
 scalar_t__ rtw_mp_mode ; 
 scalar_t__ rtw_network_mode ; 
 scalar_t__ rtw_notch_filter ; 
 scalar_t__ rtw_power_mgnt ; 
 scalar_t__ rtw_preamble ; 
 scalar_t__ rtw_radio_enable ; 
 scalar_t__ rtw_rf_config ; 
 scalar_t__ rtw_rfintfs ; 
 scalar_t__ rtw_rts_thresh ; 
 scalar_t__ rtw_scan_mode ; 
 scalar_t__ rtw_short_retry_lmt ; 
 scalar_t__ rtw_soft_ap ; 
 scalar_t__ rtw_software_decrypt ; 
 scalar_t__ rtw_software_encrypt ; 
 scalar_t__ rtw_special_rf_path ; 
 scalar_t__ rtw_uapsd_acbe_en ; 
 scalar_t__ rtw_uapsd_acbk_en ; 
 scalar_t__ rtw_uapsd_acvi_en ; 
 scalar_t__ rtw_uapsd_acvo_en ; 
 scalar_t__ rtw_uapsd_enable ; 
 scalar_t__ rtw_uapsd_max_sp ; 
 scalar_t__ rtw_vcs_type ; 
 scalar_t__ rtw_vrtl_carrier_sense ; 
 scalar_t__ rtw_wifi_spec ; 
 scalar_t__ rtw_wireless_mode ; 
 scalar_t__ rtw_wmm_enable ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 

uint loadparam( _adapter *padapter,  _nic_hdl	pnetdev)
{

	uint status = _SUCCESS;
	struct registry_priv  *registry_par = &padapter->registrypriv;

_func_enter_;

	registry_par->chip_version = (u8)rtw_chip_version;
	registry_par->rfintfs = (u8)rtw_rfintfs;
	registry_par->lbkmode = (u8)rtw_lbkmode;
	//registry_par->hci = (u8)hci;
	registry_par->network_mode  = (u8)rtw_network_mode;

	_rtw_memcpy(registry_par->ssid.Ssid, "ANY", 3);
	registry_par->ssid.SsidLength = 3;

	registry_par->channel = (u8)rtw_channel;
	registry_par->wireless_mode = (u8)rtw_wireless_mode;
	registry_par->vrtl_carrier_sense = (u8)rtw_vrtl_carrier_sense ;
	registry_par->vcs_type = (u8)rtw_vcs_type;
	registry_par->rts_thresh=(u16)rtw_rts_thresh;
	registry_par->frag_thresh=(u16)rtw_frag_thresh;
	registry_par->preamble = (u8)rtw_preamble;
	registry_par->scan_mode = (u8)rtw_scan_mode;
	registry_par->adhoc_tx_pwr = (u8)rtw_adhoc_tx_pwr;
	registry_par->soft_ap=  (u8)rtw_soft_ap;
	//registry_par->smart_ps =  (u8)rtw_smart_ps;
	registry_par->power_mgnt = (u8)rtw_power_mgnt;
	registry_par->ips_mode = (u8)rtw_ips_mode;
	registry_par->radio_enable = (u8)rtw_radio_enable;
	registry_par->long_retry_lmt = (u8)rtw_long_retry_lmt;
	registry_par->short_retry_lmt = (u8)rtw_short_retry_lmt;
  	registry_par->busy_thresh = (u16)rtw_busy_thresh;
  	//registry_par->qos_enable = (u8)rtw_qos_enable;
	registry_par->ack_policy = (u8)rtw_ack_policy;
	registry_par->mp_mode = (u8)rtw_mp_mode;
	registry_par->software_encrypt = (u8)rtw_software_encrypt;
	registry_par->software_decrypt = (u8)rtw_software_decrypt;

	registry_par->acm_method = (u8)rtw_acm_method;

	 //UAPSD
	registry_par->wmm_enable = (u8)rtw_wmm_enable;
	registry_par->uapsd_enable = (u8)rtw_uapsd_enable;
	registry_par->uapsd_max_sp = (u8)rtw_uapsd_max_sp;
	registry_par->uapsd_acbk_en = (u8)rtw_uapsd_acbk_en;
	registry_par->uapsd_acbe_en = (u8)rtw_uapsd_acbe_en;
	registry_par->uapsd_acvi_en = (u8)rtw_uapsd_acvi_en;
	registry_par->uapsd_acvo_en = (u8)rtw_uapsd_acvo_en;

#ifdef CONFIG_80211N_HT
	registry_par->ht_enable = (u8)rtw_ht_enable;
	registry_par->cbw40_enable = (u8)rtw_cbw40_enable;
	registry_par->ampdu_enable = (u8)rtw_ampdu_enable;
	registry_par->rx_stbc = (u8)rtw_rx_stbc;
	registry_par->ampdu_amsdu = (u8)rtw_ampdu_amsdu;
#endif

	registry_par->lowrate_two_xmit = (u8)rtw_lowrate_two_xmit;
	registry_par->rf_config = (u8)rtw_rf_config;
	registry_par->low_power = (u8)rtw_low_power;


	registry_par->wifi_spec = (u8)rtw_wifi_spec;
	registry_par->special_rf_path = (u8)rtw_special_rf_path;
	registry_par->channel_plan = (u8)rtw_channel_plan;

#ifdef CONFIG_BT_COEXIST
	registry_par->bt_iso = (u8)rtw_bt_iso;
	registry_par->bt_sco = (u8)rtw_bt_sco;
	registry_par->bt_ampdu = (u8)rtw_bt_ampdu;
#endif
	registry_par->bAcceptAddbaReq = (u8)rtw_AcceptAddbaReq;

	registry_par->antdiv_cfg = (u8)rtw_antdiv_cfg;

#ifdef CONFIG_AUTOSUSPEND
	registry_par->usbss_enable = (u8)rtw_enusbss;//0:disable,1:enable
#endif
#ifdef SUPPORT_HW_RFOFF_DETECTED
	registry_par->hwpdn_mode = (u8)rtw_hwpdn_mode;//0:disable,1:enable,2:by EFUSE config
	registry_par->hwpwrp_detect = (u8)rtw_hwpwrp_detect;//0:disable,1:enable
#endif

	registry_par->hw_wps_pbc = (u8)rtw_hw_wps_pbc;

#ifdef CONFIG_ADAPTOR_INFO_CACHING_FILE
	snprintf(registry_par->adaptor_info_caching_file_path, PATH_LENGTH_MAX, "%s", rtw_adaptor_info_caching_file_path);
	registry_par->adaptor_info_caching_file_path[PATH_LENGTH_MAX-1]=0;
#endif

#ifdef CONFIG_LAYER2_ROAMING
	registry_par->max_roaming_times = (u8)rtw_max_roaming_times;
#ifdef CONFIG_INTEL_WIDI
	registry_par->max_roaming_times = (u8)rtw_max_roaming_times + 2;
#endif // CONFIG_INTEL_WIDI
#endif

#ifdef CONFIG_IOL
	registry_par->force_iol = rtw_force_iol;
#endif

	registry_par->mac_phy_mode = rtw_mac_phy_mode;

#ifdef CONFIG_80211D
	registry_par->enable80211d = (u8)rtw_80211d;
#endif

	snprintf(registry_par->ifname, 16, "%s", ifname);
	snprintf(registry_par->if2name, 16, "%s", if2name);

	registry_par->notch_filter = (u8)rtw_notch_filter;

#ifdef CONFIG_MULTI_VIR_IFACES
	registry_par->ext_iface_num = (u8)rtw_ext_iface_num;
#endif //CONFIG_MULTI_VIR_IFACES

_func_exit_;

	return status;
}