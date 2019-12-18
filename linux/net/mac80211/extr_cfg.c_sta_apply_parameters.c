#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_14__ {scalar_t__ type; int /*<<< orphan*/  power; } ;
struct station_parameters {int sta_flags_mask; int sta_flags_set; int ext_capab_len; int* ext_capab; int sta_modify_mask; scalar_t__ listen_interval; scalar_t__ support_p2p_ps; scalar_t__ airtime_weight; int /*<<< orphan*/  opmode_notif; scalar_t__ opmode_notif_used; int /*<<< orphan*/  he_capa_len; scalar_t__ he_capa; int /*<<< orphan*/  vht_capa; int /*<<< orphan*/  ht_capa; int /*<<< orphan*/  supported_rates_len; int /*<<< orphan*/  supported_rates; TYPE_6__ txpwr; scalar_t__ aid; int /*<<< orphan*/  max_sp; int /*<<< orphan*/  uapsd_queues; } ;
struct TYPE_12__ {scalar_t__ type; int /*<<< orphan*/  power; } ;
struct TYPE_13__ {int wme; int mfp; int max_amsdu_subframes; scalar_t__ support_p2p_ps; int /*<<< orphan*/ * supp_rates; TYPE_4__ txpwr; scalar_t__ aid; int /*<<< orphan*/  max_sp; int /*<<< orphan*/  uapsd_queues; } ;
struct sta_info {scalar_t__ listen_interval; scalar_t__ airtime_weight; TYPE_5__ sta; struct ieee80211_sub_if_data* sdata; } ;
struct ieee80211_supported_band {size_t band; } ;
struct TYPE_9__ {int /*<<< orphan*/  chandef; } ;
struct TYPE_15__ {TYPE_1__ bss_conf; } ;
struct TYPE_10__ {int /*<<< orphan*/  tdls_wider_bw_prohibited; int /*<<< orphan*/  tdls_chan_switch_prohibited; } ;
struct TYPE_11__ {TYPE_2__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_7__ vif; TYPE_3__ u; } ;
struct TYPE_16__ {scalar_t__ queues; } ;
struct ieee80211_local {TYPE_8__ hw; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_ASSOCIATED ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_AUTHENTICATED ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_AUTHORIZED ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_MFP ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_TDLS_PEER ; 
 int /*<<< orphan*/  NL80211_STA_FLAG_WME ; 
 scalar_t__ NL80211_TX_POWER_LIMITED ; 
 int STATION_PARAM_APPLY_STA_TXPOWER ; 
 int STATION_PARAM_APPLY_UAPSD ; 
 int /*<<< orphan*/  TDLS_WIDER_BW ; 
 int WLAN_EXT_CAPA4_TDLS_CHAN_SWITCH ; 
 int WLAN_EXT_CAPA8_MAX_MSDU_IN_AMSDU_LSB ; 
 int WLAN_EXT_CAPA8_TDLS_WIDE_BW_ENABLED ; 
 int WLAN_EXT_CAPA9_MAX_MSDU_IN_AMSDU_MSB ; 
 int /*<<< orphan*/  WLAN_STA_MFP ; 
 int /*<<< orphan*/  WLAN_STA_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  WLAN_STA_TDLS_CHAN_SWITCH ; 
 int /*<<< orphan*/  WLAN_STA_TDLS_PEER ; 
 int /*<<< orphan*/  WLAN_STA_TDLS_WIDER_BW ; 
 int /*<<< orphan*/  __ieee80211_vht_handle_opmode (struct ieee80211_sub_if_data*,struct sta_info*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  clear_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int drv_sta_set_txpwr (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct sta_info*) ; 
 struct ieee80211_supported_band* ieee80211_get_sband (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_he_cap_ie_to_sta_he_cap (struct ieee80211_sub_if_data*,struct ieee80211_supported_band*,void*,int /*<<< orphan*/ ,struct sta_info*) ; 
 int /*<<< orphan*/  ieee80211_ht_cap_ie_to_sta_ht_cap (struct ieee80211_sub_if_data*,struct ieee80211_supported_band*,int /*<<< orphan*/ ,struct sta_info*) ; 
 scalar_t__ ieee80211_hw_check (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_parse_bitrates (int /*<<< orphan*/ *,struct ieee80211_supported_band*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_vht_cap_ie_to_sta_vht_cap (struct ieee80211_sub_if_data*,struct ieee80211_supported_band*,int /*<<< orphan*/ ,struct sta_info*) ; 
 scalar_t__ ieee80211_vif_is_mesh (TYPE_7__*) ; 
 int /*<<< orphan*/  set_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int sta_apply_auth_flags (struct ieee80211_local*,struct sta_info*,int,int) ; 
 int /*<<< orphan*/  sta_apply_mesh_params (struct ieee80211_local*,struct sta_info*,struct station_parameters*) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sta_apply_parameters(struct ieee80211_local *local,
				struct sta_info *sta,
				struct station_parameters *params)
{
	int ret = 0;
	struct ieee80211_supported_band *sband;
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	u32 mask, set;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		return -EINVAL;

	mask = params->sta_flags_mask;
	set = params->sta_flags_set;

	if (ieee80211_vif_is_mesh(&sdata->vif)) {
		/*
		 * In mesh mode, ASSOCIATED isn't part of the nl80211
		 * API but must follow AUTHENTICATED for driver state.
		 */
		if (mask & BIT(NL80211_STA_FLAG_AUTHENTICATED))
			mask |= BIT(NL80211_STA_FLAG_ASSOCIATED);
		if (set & BIT(NL80211_STA_FLAG_AUTHENTICATED))
			set |= BIT(NL80211_STA_FLAG_ASSOCIATED);
	} else if (test_sta_flag(sta, WLAN_STA_TDLS_PEER)) {
		/*
		 * TDLS -- everything follows authorized, but
		 * only becoming authorized is possible, not
		 * going back
		 */
		if (set & BIT(NL80211_STA_FLAG_AUTHORIZED)) {
			set |= BIT(NL80211_STA_FLAG_AUTHENTICATED) |
			       BIT(NL80211_STA_FLAG_ASSOCIATED);
			mask |= BIT(NL80211_STA_FLAG_AUTHENTICATED) |
				BIT(NL80211_STA_FLAG_ASSOCIATED);
		}
	}

	if (mask & BIT(NL80211_STA_FLAG_WME) &&
	    local->hw.queues >= IEEE80211_NUM_ACS)
		sta->sta.wme = set & BIT(NL80211_STA_FLAG_WME);

	/* auth flags will be set later for TDLS,
	 * and for unassociated stations that move to assocaited */
	if (!test_sta_flag(sta, WLAN_STA_TDLS_PEER) &&
	    !((mask & BIT(NL80211_STA_FLAG_ASSOCIATED)) &&
	      (set & BIT(NL80211_STA_FLAG_ASSOCIATED)))) {
		ret = sta_apply_auth_flags(local, sta, mask, set);
		if (ret)
			return ret;
	}

	if (mask & BIT(NL80211_STA_FLAG_SHORT_PREAMBLE)) {
		if (set & BIT(NL80211_STA_FLAG_SHORT_PREAMBLE))
			set_sta_flag(sta, WLAN_STA_SHORT_PREAMBLE);
		else
			clear_sta_flag(sta, WLAN_STA_SHORT_PREAMBLE);
	}

	if (mask & BIT(NL80211_STA_FLAG_MFP)) {
		sta->sta.mfp = !!(set & BIT(NL80211_STA_FLAG_MFP));
		if (set & BIT(NL80211_STA_FLAG_MFP))
			set_sta_flag(sta, WLAN_STA_MFP);
		else
			clear_sta_flag(sta, WLAN_STA_MFP);
	}

	if (mask & BIT(NL80211_STA_FLAG_TDLS_PEER)) {
		if (set & BIT(NL80211_STA_FLAG_TDLS_PEER))
			set_sta_flag(sta, WLAN_STA_TDLS_PEER);
		else
			clear_sta_flag(sta, WLAN_STA_TDLS_PEER);
	}

	/* mark TDLS channel switch support, if the AP allows it */
	if (test_sta_flag(sta, WLAN_STA_TDLS_PEER) &&
	    !sdata->u.mgd.tdls_chan_switch_prohibited &&
	    params->ext_capab_len >= 4 &&
	    params->ext_capab[3] & WLAN_EXT_CAPA4_TDLS_CHAN_SWITCH)
		set_sta_flag(sta, WLAN_STA_TDLS_CHAN_SWITCH);

	if (test_sta_flag(sta, WLAN_STA_TDLS_PEER) &&
	    !sdata->u.mgd.tdls_wider_bw_prohibited &&
	    ieee80211_hw_check(&local->hw, TDLS_WIDER_BW) &&
	    params->ext_capab_len >= 8 &&
	    params->ext_capab[7] & WLAN_EXT_CAPA8_TDLS_WIDE_BW_ENABLED)
		set_sta_flag(sta, WLAN_STA_TDLS_WIDER_BW);

	if (params->sta_modify_mask & STATION_PARAM_APPLY_UAPSD) {
		sta->sta.uapsd_queues = params->uapsd_queues;
		sta->sta.max_sp = params->max_sp;
	}

	/* The sender might not have sent the last bit, consider it to be 0 */
	if (params->ext_capab_len >= 8) {
		u8 val = (params->ext_capab[7] &
			  WLAN_EXT_CAPA8_MAX_MSDU_IN_AMSDU_LSB) >> 7;

		/* we did get all the bits, take the MSB as well */
		if (params->ext_capab_len >= 9) {
			u8 val_msb = params->ext_capab[8] &
				WLAN_EXT_CAPA9_MAX_MSDU_IN_AMSDU_MSB;
			val_msb <<= 1;
			val |= val_msb;
		}

		switch (val) {
		case 1:
			sta->sta.max_amsdu_subframes = 32;
			break;
		case 2:
			sta->sta.max_amsdu_subframes = 16;
			break;
		case 3:
			sta->sta.max_amsdu_subframes = 8;
			break;
		default:
			sta->sta.max_amsdu_subframes = 0;
		}
	}

	/*
	 * cfg80211 validates this (1-2007) and allows setting the AID
	 * only when creating a new station entry
	 */
	if (params->aid)
		sta->sta.aid = params->aid;

	/*
	 * Some of the following updates would be racy if called on an
	 * existing station, via ieee80211_change_station(). However,
	 * all such changes are rejected by cfg80211 except for updates
	 * changing the supported rates on an existing but not yet used
	 * TDLS peer.
	 */

	if (params->listen_interval >= 0)
		sta->listen_interval = params->listen_interval;

	if (params->sta_modify_mask & STATION_PARAM_APPLY_STA_TXPOWER) {
		sta->sta.txpwr.type = params->txpwr.type;
		if (params->txpwr.type == NL80211_TX_POWER_LIMITED)
			sta->sta.txpwr.power = params->txpwr.power;
		ret = drv_sta_set_txpwr(local, sdata, sta);
		if (ret)
			return ret;
	}

	if (params->supported_rates && params->supported_rates_len) {
		ieee80211_parse_bitrates(&sdata->vif.bss_conf.chandef,
					 sband, params->supported_rates,
					 params->supported_rates_len,
					 &sta->sta.supp_rates[sband->band]);
	}

	if (params->ht_capa)
		ieee80211_ht_cap_ie_to_sta_ht_cap(sdata, sband,
						  params->ht_capa, sta);

	/* VHT can override some HT caps such as the A-MSDU max length */
	if (params->vht_capa)
		ieee80211_vht_cap_ie_to_sta_vht_cap(sdata, sband,
						    params->vht_capa, sta);

	if (params->he_capa)
		ieee80211_he_cap_ie_to_sta_he_cap(sdata, sband,
						  (void *)params->he_capa,
						  params->he_capa_len, sta);

	if (params->opmode_notif_used) {
		/* returned value is only needed for rc update, but the
		 * rc isn't initialized here yet, so ignore it
		 */
		__ieee80211_vht_handle_opmode(sdata, sta, params->opmode_notif,
					      sband->band);
	}

	if (params->support_p2p_ps >= 0)
		sta->sta.support_p2p_ps = params->support_p2p_ps;

	if (ieee80211_vif_is_mesh(&sdata->vif))
		sta_apply_mesh_params(local, sta, params);

	if (params->airtime_weight)
		sta->airtime_weight = params->airtime_weight;

	/* set the STA state after all sta info from usermode has been set */
	if (test_sta_flag(sta, WLAN_STA_TDLS_PEER) ||
	    set & BIT(NL80211_STA_FLAG_ASSOCIATED)) {
		ret = sta_apply_auth_flags(local, sta, mask, set);
		if (ret)
			return ret;
	}

	return 0;
}