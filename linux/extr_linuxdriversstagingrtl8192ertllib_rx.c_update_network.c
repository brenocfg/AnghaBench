#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct rtllib_tim_parameters {int dummy; } ;
struct rtllib_rx_stats {int dummy; } ;
struct rtllib_qos_data {int dummy; } ;
struct TYPE_6__ {int active; int supported; scalar_t__ ac_aci_acm_aifsn; int /*<<< orphan*/  old_param_count; int /*<<< orphan*/  param_count; } ;
struct TYPE_5__ {int bdHTCapLen; int bdHTInfoLen; int /*<<< orphan*/  bdRT2RTLongSlotTime; int /*<<< orphan*/  bdHTSpecVer; TYPE_2__* bdHTInfoBuf; TYPE_2__* bdHTCapBuf; int /*<<< orphan*/  bdRT2RTAggregation; int /*<<< orphan*/  bdSupportHT; } ;
struct rtllib_network {int rates_len; int rates_ex_len; int ssid_len; int hidden_ssid_len; int flags; int berp_info_valid; int wpa_ie_len; int rsn_ie_len; int wzc_ie_len; int CountryIeLen; int /*<<< orphan*/  BssCcxVerNumber; int /*<<< orphan*/  bWithCcxVerNum; TYPE_2__* MBssid; int /*<<< orphan*/  bMBssidValid; int /*<<< orphan*/  MBssidMask; int /*<<< orphan*/  bCcxRmEnable; TYPE_2__* CcxRmState; int /*<<< orphan*/  bCkipSupported; int /*<<< orphan*/  bWithAironetIE; TYPE_2__* CountryIeBuf; int /*<<< orphan*/  Turbo_Enable; int /*<<< orphan*/  RSSI; int /*<<< orphan*/  SignalStrength; TYPE_2__* wmm_param; int /*<<< orphan*/  wmm_info; TYPE_2__ qos_data; TYPE_2__* ssid; int /*<<< orphan*/  last_scanned; TYPE_2__* wzc_ie; TYPE_2__* rsn_ie; TYPE_2__* wpa_ie; int /*<<< orphan*/  unknown_cap_exist; int /*<<< orphan*/  airgo_cap_exist; int /*<<< orphan*/  cisco_cap_exist; int /*<<< orphan*/  marvell_cap_exist; int /*<<< orphan*/  realtek_cap_exit; int /*<<< orphan*/  atheros_cap_exist; int /*<<< orphan*/  ralink_cap_exist; int /*<<< orphan*/  broadcom_cap_exist; TYPE_1__ bssht; TYPE_2__ tim; int /*<<< orphan*/  last_dtim_sta_time; int /*<<< orphan*/  dtim_data; int /*<<< orphan*/  dtim_period; int /*<<< orphan*/  atim_window; int /*<<< orphan*/  listen_interval; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  erp_value; int /*<<< orphan*/ * time_stamp; int /*<<< orphan*/  mode; TYPE_2__* hidden_ssid; TYPE_2__* rates_ex; TYPE_2__* rates; int /*<<< orphan*/  capability; TYPE_2__ stats; } ;
struct rtllib_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NETWORK_HAS_ERP_VALUE ; 
 int NETWORK_HAS_QOS_PARAMETERS ; 
 int WME_AC_PRAM_LEN ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static inline void update_network(struct rtllib_device *ieee,
				  struct rtllib_network *dst,
				  struct rtllib_network *src)
{
	int qos_active;
	u8 old_param;

	memcpy(&dst->stats, &src->stats, sizeof(struct rtllib_rx_stats));
	dst->capability = src->capability;
	memcpy(dst->rates, src->rates, src->rates_len);
	dst->rates_len = src->rates_len;
	memcpy(dst->rates_ex, src->rates_ex, src->rates_ex_len);
	dst->rates_ex_len = src->rates_ex_len;
	if (src->ssid_len > 0) {
		if (dst->ssid_len == 0) {
			memset(dst->hidden_ssid, 0, sizeof(dst->hidden_ssid));
			dst->hidden_ssid_len = src->ssid_len;
			memcpy(dst->hidden_ssid, src->ssid, src->ssid_len);
		} else {
			memset(dst->ssid, 0, dst->ssid_len);
			dst->ssid_len = src->ssid_len;
			memcpy(dst->ssid, src->ssid, src->ssid_len);
		}
	}
	dst->mode = src->mode;
	dst->flags = src->flags;
	dst->time_stamp[0] = src->time_stamp[0];
	dst->time_stamp[1] = src->time_stamp[1];
	if (src->flags & NETWORK_HAS_ERP_VALUE) {
		dst->erp_value = src->erp_value;
		dst->berp_info_valid = src->berp_info_valid = true;
	}
	dst->beacon_interval = src->beacon_interval;
	dst->listen_interval = src->listen_interval;
	dst->atim_window = src->atim_window;
	dst->dtim_period = src->dtim_period;
	dst->dtim_data = src->dtim_data;
	dst->last_dtim_sta_time = src->last_dtim_sta_time;
	memcpy(&dst->tim, &src->tim, sizeof(struct rtllib_tim_parameters));

	dst->bssht.bdSupportHT = src->bssht.bdSupportHT;
	dst->bssht.bdRT2RTAggregation = src->bssht.bdRT2RTAggregation;
	dst->bssht.bdHTCapLen = src->bssht.bdHTCapLen;
	memcpy(dst->bssht.bdHTCapBuf, src->bssht.bdHTCapBuf,
	       src->bssht.bdHTCapLen);
	dst->bssht.bdHTInfoLen = src->bssht.bdHTInfoLen;
	memcpy(dst->bssht.bdHTInfoBuf, src->bssht.bdHTInfoBuf,
	       src->bssht.bdHTInfoLen);
	dst->bssht.bdHTSpecVer = src->bssht.bdHTSpecVer;
	dst->bssht.bdRT2RTLongSlotTime = src->bssht.bdRT2RTLongSlotTime;
	dst->broadcom_cap_exist = src->broadcom_cap_exist;
	dst->ralink_cap_exist = src->ralink_cap_exist;
	dst->atheros_cap_exist = src->atheros_cap_exist;
	dst->realtek_cap_exit = src->realtek_cap_exit;
	dst->marvell_cap_exist = src->marvell_cap_exist;
	dst->cisco_cap_exist = src->cisco_cap_exist;
	dst->airgo_cap_exist = src->airgo_cap_exist;
	dst->unknown_cap_exist = src->unknown_cap_exist;
	memcpy(dst->wpa_ie, src->wpa_ie, src->wpa_ie_len);
	dst->wpa_ie_len = src->wpa_ie_len;
	memcpy(dst->rsn_ie, src->rsn_ie, src->rsn_ie_len);
	dst->rsn_ie_len = src->rsn_ie_len;
	memcpy(dst->wzc_ie, src->wzc_ie, src->wzc_ie_len);
	dst->wzc_ie_len = src->wzc_ie_len;

	dst->last_scanned = jiffies;
	/* qos related parameters */
	qos_active = dst->qos_data.active;
	old_param = dst->qos_data.param_count;
	dst->qos_data.supported = src->qos_data.supported;
	if (dst->flags & NETWORK_HAS_QOS_PARAMETERS)
		memcpy(&dst->qos_data, &src->qos_data,
		       sizeof(struct rtllib_qos_data));
	if (dst->qos_data.supported == 1) {
		if (dst->ssid_len)
			netdev_dbg(ieee->dev,
				   "QoS the network %s is QoS supported\n",
				   dst->ssid);
		else
			netdev_dbg(ieee->dev,
				   "QoS the network is QoS supported\n");
	}
	dst->qos_data.active = qos_active;
	dst->qos_data.old_param_count = old_param;

	dst->wmm_info = src->wmm_info;
	if (src->wmm_param[0].ac_aci_acm_aifsn ||
	   src->wmm_param[1].ac_aci_acm_aifsn ||
	   src->wmm_param[2].ac_aci_acm_aifsn ||
	   src->wmm_param[3].ac_aci_acm_aifsn)
		memcpy(dst->wmm_param, src->wmm_param, WME_AC_PRAM_LEN);

	dst->SignalStrength = src->SignalStrength;
	dst->RSSI = src->RSSI;
	dst->Turbo_Enable = src->Turbo_Enable;

	dst->CountryIeLen = src->CountryIeLen;
	memcpy(dst->CountryIeBuf, src->CountryIeBuf, src->CountryIeLen);

	dst->bWithAironetIE = src->bWithAironetIE;
	dst->bCkipSupported = src->bCkipSupported;
	memcpy(dst->CcxRmState, src->CcxRmState, 2);
	dst->bCcxRmEnable = src->bCcxRmEnable;
	dst->MBssidMask = src->MBssidMask;
	dst->bMBssidValid = src->bMBssidValid;
	memcpy(dst->MBssid, src->MBssid, 6);
	dst->bWithCcxVerNum = src->bWithCcxVerNum;
	dst->BssCcxVerNumber = src->BssCcxVerNumber;
}