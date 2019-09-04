#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rtl_tcb_desc {int use_spe_rpt; int use_driver_rate; int disable_ratefallback; int packet_bw; int multicast; int broadcast; int /*<<< orphan*/  hw_rate; void* ratr_index; scalar_t__ mac_id; } ;
struct rtl_sta_info {int /*<<< orphan*/  wireless_mode; } ;
struct rtl_priv {TYPE_5__* cfg; } ;
struct rtl_mac {scalar_t__ mode; } ;
struct TYPE_7__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {TYPE_2__ control; } ;
struct TYPE_9__ {scalar_t__ ht_supported; } ;
struct TYPE_8__ {scalar_t__ vht_supported; } ;
struct ieee80211_sta {TYPE_4__ ht_cap; TYPE_3__ vht_cap; scalar_t__ drv_priv; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; } ;
typedef  enum rtl_var_map { ____Placeholder_rtl_var_map } rtl_var_map ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_10__ {int spec_ver; int /*<<< orphan*/ * maps; } ;
struct TYPE_6__ {scalar_t__ idx; } ;

/* Variables and functions */
 void* RATR_INX_WIRELESS_MC ; 
 int RTL_RC_CCK_RATE11M ; 
 int RTL_RC_OFDM_RATE54M ; 
 int RTL_SPEC_NEW_RATEID ; 
 scalar_t__ WIRELESS_MODE_B ; 
 int /*<<< orphan*/  WIRELESS_MODE_G ; 
 int /*<<< orphan*/  _rtl_get_highest_n_rate (struct ieee80211_hw*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  _rtl_get_tx_hw_rate (struct ieee80211_hw*,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  _rtl_get_vht_highest_n_rate (struct ieee80211_hw*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  _rtl_query_bandwidth_mode (struct ieee80211_hw*,struct ieee80211_sta*,struct rtl_tcb_desc*) ; 
 int /*<<< orphan*/  _rtl_query_protection_mode (struct ieee80211_hw*,struct rtl_tcb_desc*,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  _rtl_query_shortgi (struct ieee80211_hw*,struct ieee80211_sta*,struct rtl_tcb_desc*,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  _rtl_qurey_shortpreamble_mode (struct ieee80211_hw*,struct rtl_tcb_desc*,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  _rtl_txrate_selectmode (struct ieee80211_hw*,struct ieee80211_sta*,struct rtl_tcb_desc*) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_nullfunc (int /*<<< orphan*/ ) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_get_fc (struct sk_buff*) ; 
 struct ieee80211_hdr* rtl_get_hdr (struct sk_buff*) ; 
 scalar_t__ rtl_is_tx_report_skb (struct ieee80211_hw*,struct sk_buff*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 void* rtl_mrate_idx_to_arfr_id (struct ieee80211_hw*,void*,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl_get_tcb_desc(struct ieee80211_hw *hw,
		      struct ieee80211_tx_info *info,
		      struct ieee80211_sta *sta,
		      struct sk_buff *skb, struct rtl_tcb_desc *tcb_desc)
{
#define SET_RATE_ID(rate_id)					\
	((rtlpriv->cfg->spec_ver & RTL_SPEC_NEW_RATEID) ?	\
		rtl_mrate_idx_to_arfr_id(hw, rate_id,		\
			(sta_entry ? sta_entry->wireless_mode :	\
			 WIRELESS_MODE_G)) :			\
		rate_id)

	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *rtlmac = rtl_mac(rtl_priv(hw));
	struct ieee80211_hdr *hdr = rtl_get_hdr(skb);
	struct rtl_sta_info *sta_entry =
		(sta ? (struct rtl_sta_info *)sta->drv_priv : NULL);

	__le16 fc = rtl_get_fc(skb);

	tcb_desc->hw_rate = _rtl_get_tx_hw_rate(hw, info);

	if (rtl_is_tx_report_skb(hw, skb))
		tcb_desc->use_spe_rpt = 1;

	if (!ieee80211_is_data(fc)) {
		tcb_desc->use_driver_rate = true;
		tcb_desc->ratr_index = SET_RATE_ID(RATR_INX_WIRELESS_MC);
		tcb_desc->disable_ratefallback = 1;
		tcb_desc->mac_id = 0;
		tcb_desc->packet_bw = false;

		return;
	}

	/*
	 * We set data rate INX 0
	 * in rtl_rc.c if skb is special data or
	 * mgt which need low data rate.
	 */

	/*
	 * So tcb_desc->hw_rate is just used for
	 * special data and mgt frames
	 */
	if (info->control.rates[0].idx == 0 || ieee80211_is_nullfunc(fc)) {
		tcb_desc->use_driver_rate = true;
		tcb_desc->ratr_index = SET_RATE_ID(RATR_INX_WIRELESS_MC);

		tcb_desc->disable_ratefallback = 1;
	} else if (sta && sta->vht_cap.vht_supported) {
		/*
		 * Because hw will never use hw_rate
		 * when tcb_desc->use_driver_rate = false
		 * so we never set highest N rate here,
		 * and N rate will all be controlled by FW
		 * when tcb_desc->use_driver_rate = false
		 */
		tcb_desc->hw_rate = _rtl_get_vht_highest_n_rate(hw, sta);
	} else if (sta && sta->ht_cap.ht_supported) {
		tcb_desc->hw_rate = _rtl_get_highest_n_rate(hw, sta);
	} else {
		enum rtl_var_map var = RTL_RC_OFDM_RATE54M;

		if (rtlmac->mode == WIRELESS_MODE_B)
			var = RTL_RC_CCK_RATE11M;

		tcb_desc->hw_rate = rtlpriv->cfg->maps[var];
	}

	if (is_multicast_ether_addr(hdr->addr1))
		tcb_desc->multicast = 1;
	else if (is_broadcast_ether_addr(hdr->addr1))
		tcb_desc->broadcast = 1;

	_rtl_txrate_selectmode(hw, sta, tcb_desc);
	_rtl_query_bandwidth_mode(hw, sta, tcb_desc);
	_rtl_qurey_shortpreamble_mode(hw, tcb_desc, info);
	_rtl_query_shortgi(hw, sta, tcb_desc, info);
	_rtl_query_protection_mode(hw, tcb_desc, info);
#undef SET_RATE_ID
}