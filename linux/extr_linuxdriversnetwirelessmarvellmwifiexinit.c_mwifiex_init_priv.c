#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct mwifiex_wep_key {int dummy; } ;
struct TYPE_2__ {scalar_t__ encryption_mode; int /*<<< orphan*/  authentication_mode; scalar_t__ wep_enabled; } ;
struct mwifiex_private {int media_connected; int port_open; int is_data_rate_auto; int curr_pkt_filter; int beacon_period; int wpa_is_gtk_set; int wmm_required; int wmm_enabled; int scan_block; int hs2_enabled; int check_tdls_tx; int /*<<< orphan*/  tos_to_tid_inv; scalar_t__ del_list_idx; scalar_t__ csa_expire_time; scalar_t__ csa_chan; int /*<<< orphan*/  roc_cfg; scalar_t__ ap_11n_enabled; scalar_t__ wps_ie_len; int /*<<< orphan*/ * wps_ie; scalar_t__ curr_bcn_size; int /*<<< orphan*/ * curr_bcn_buf; scalar_t__ wmm_qosinfo; int /*<<< orphan*/ * vs_ie; scalar_t__ gen_ie_buf_len; int /*<<< orphan*/  gen_ie_buf; int /*<<< orphan*/  wps; scalar_t__ assoc_tlv_buf_len; int /*<<< orphan*/  assoc_tlv_buf; scalar_t__ wpa_ie_len; int /*<<< orphan*/  aes_key; int /*<<< orphan*/  wpa_ie; scalar_t__ bcn_nf_last; scalar_t__ bcn_nf_avg; scalar_t__ bcn_rssi_avg; scalar_t__ bcn_rssi_last; scalar_t__ data_nf_last; scalar_t__ data_nf_avg; scalar_t__ data_rssi_avg; scalar_t__ data_rssi_last; scalar_t__ rate_bitmap; scalar_t__ rxpd_rate; scalar_t__ rxpd_htinfo; scalar_t__ tx_rate; scalar_t__ rx_ant; scalar_t__ tx_ant; scalar_t__ min_tx_power_level; scalar_t__ max_tx_power_level; scalar_t__ tx_power_level; int /*<<< orphan*/  adhoc_state; scalar_t__ atim_window; int /*<<< orphan*/  adhoc_channel; scalar_t__ assoc_rsp_size; int /*<<< orphan*/  assoc_rsp_buf; int /*<<< orphan*/  prev_bssid; int /*<<< orphan*/  prev_ssid; int /*<<< orphan*/  listen_interval; int /*<<< orphan*/  curr_bss_params; int /*<<< orphan*/ * attempted_bss_desc; scalar_t__ wep_key_curr_index; int /*<<< orphan*/ * wep_key; TYPE_1__ sec_info; int /*<<< orphan*/  data_avg_factor; int /*<<< orphan*/  bcn_avg_factor; scalar_t__ data_rate; int /*<<< orphan*/  bss_mode; scalar_t__ pkt_tx_ctrl; int /*<<< orphan*/  usb_port; int /*<<< orphan*/  curr_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADHOC_IDLE ; 
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEFAULT_AD_HOC_CHANNEL ; 
 int /*<<< orphan*/  DEFAULT_BCN_AVG_FACTOR ; 
 int /*<<< orphan*/  DEFAULT_DATA_AVG_FACTOR ; 
 int HostCmd_ACT_MAC_DYNAMIC_BW_ENABLE ; 
 int HostCmd_ACT_MAC_ETHERNETII_ENABLE ; 
 int HostCmd_ACT_MAC_RX_ON ; 
 int HostCmd_ACT_MAC_TX_ON ; 
 int /*<<< orphan*/  MAX_NUM_TID ; 
 int /*<<< orphan*/  MWIFIEX_DEFAULT_LISTEN_INTERVAL ; 
 int /*<<< orphan*/  MWIFIEX_USB_EP_DATA ; 
 int /*<<< orphan*/  NL80211_AUTHTYPE_OPEN_SYSTEM ; 
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  eth_broadcast_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mwifiex_add_bss_prio_tbl (struct mwifiex_private*) ; 
 int /*<<< orphan*/  mwifiex_init_11h_params (struct mwifiex_private*) ; 
 int /*<<< orphan*/  tos_to_tid_inv ; 

int mwifiex_init_priv(struct mwifiex_private *priv)
{
	u32 i;

	priv->media_connected = false;
	eth_broadcast_addr(priv->curr_addr);
	priv->port_open = false;
	priv->usb_port = MWIFIEX_USB_EP_DATA;
	priv->pkt_tx_ctrl = 0;
	priv->bss_mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->data_rate = 0;	/* Initially indicate the rate as auto */
	priv->is_data_rate_auto = true;
	priv->bcn_avg_factor = DEFAULT_BCN_AVG_FACTOR;
	priv->data_avg_factor = DEFAULT_DATA_AVG_FACTOR;

	priv->sec_info.wep_enabled = 0;
	priv->sec_info.authentication_mode = NL80211_AUTHTYPE_OPEN_SYSTEM;
	priv->sec_info.encryption_mode = 0;
	for (i = 0; i < ARRAY_SIZE(priv->wep_key); i++)
		memset(&priv->wep_key[i], 0, sizeof(struct mwifiex_wep_key));
	priv->wep_key_curr_index = 0;
	priv->curr_pkt_filter = HostCmd_ACT_MAC_DYNAMIC_BW_ENABLE |
				HostCmd_ACT_MAC_RX_ON | HostCmd_ACT_MAC_TX_ON |
				HostCmd_ACT_MAC_ETHERNETII_ENABLE;

	priv->beacon_period = 100; /* beacon interval */
	priv->attempted_bss_desc = NULL;
	memset(&priv->curr_bss_params, 0, sizeof(priv->curr_bss_params));
	priv->listen_interval = MWIFIEX_DEFAULT_LISTEN_INTERVAL;

	memset(&priv->prev_ssid, 0, sizeof(priv->prev_ssid));
	memset(&priv->prev_bssid, 0, sizeof(priv->prev_bssid));
	memset(&priv->assoc_rsp_buf, 0, sizeof(priv->assoc_rsp_buf));
	priv->assoc_rsp_size = 0;
	priv->adhoc_channel = DEFAULT_AD_HOC_CHANNEL;
	priv->atim_window = 0;
	priv->adhoc_state = ADHOC_IDLE;
	priv->tx_power_level = 0;
	priv->max_tx_power_level = 0;
	priv->min_tx_power_level = 0;
	priv->tx_ant = 0;
	priv->rx_ant = 0;
	priv->tx_rate = 0;
	priv->rxpd_htinfo = 0;
	priv->rxpd_rate = 0;
	priv->rate_bitmap = 0;
	priv->data_rssi_last = 0;
	priv->data_rssi_avg = 0;
	priv->data_nf_avg = 0;
	priv->data_nf_last = 0;
	priv->bcn_rssi_last = 0;
	priv->bcn_rssi_avg = 0;
	priv->bcn_nf_avg = 0;
	priv->bcn_nf_last = 0;
	memset(&priv->wpa_ie, 0, sizeof(priv->wpa_ie));
	memset(&priv->aes_key, 0, sizeof(priv->aes_key));
	priv->wpa_ie_len = 0;
	priv->wpa_is_gtk_set = false;

	memset(&priv->assoc_tlv_buf, 0, sizeof(priv->assoc_tlv_buf));
	priv->assoc_tlv_buf_len = 0;
	memset(&priv->wps, 0, sizeof(priv->wps));
	memset(&priv->gen_ie_buf, 0, sizeof(priv->gen_ie_buf));
	priv->gen_ie_buf_len = 0;
	memset(priv->vs_ie, 0, sizeof(priv->vs_ie));

	priv->wmm_required = true;
	priv->wmm_enabled = false;
	priv->wmm_qosinfo = 0;
	priv->curr_bcn_buf = NULL;
	priv->curr_bcn_size = 0;
	priv->wps_ie = NULL;
	priv->wps_ie_len = 0;
	priv->ap_11n_enabled = 0;
	memset(&priv->roc_cfg, 0, sizeof(priv->roc_cfg));

	priv->scan_block = false;

	priv->csa_chan = 0;
	priv->csa_expire_time = 0;
	priv->del_list_idx = 0;
	priv->hs2_enabled = false;
	priv->check_tdls_tx = false;
	memcpy(priv->tos_to_tid_inv, tos_to_tid_inv, MAX_NUM_TID);

	mwifiex_init_11h_params(priv);

	return mwifiex_add_bss_prio_tbl(priv);
}