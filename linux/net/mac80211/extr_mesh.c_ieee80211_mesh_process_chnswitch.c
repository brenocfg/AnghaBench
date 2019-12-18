#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ieee802_11_elems {int dummy; } ;
struct ieee80211_supported_band {int /*<<< orphan*/  band; } ;
struct TYPE_13__ {int width; } ;
struct TYPE_15__ {TYPE_11__ chandef; } ;
struct TYPE_16__ {TYPE_2__ bss_conf; int /*<<< orphan*/  addr; } ;
struct TYPE_18__ {scalar_t__ dot11MeshTTL; } ;
struct ieee80211_if_mesh {scalar_t__ chsw_ttl; scalar_t__ pre_value; int /*<<< orphan*/  csa_role; TYPE_5__ mshcfg; int /*<<< orphan*/  userspace_handles_dfs; } ;
struct TYPE_14__ {struct ieee80211_if_mesh mesh; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  dev; TYPE_7__* local; TYPE_3__ vif; TYPE_1__ u; } ;
struct TYPE_21__ {TYPE_4__* chan; int /*<<< orphan*/  center_freq2; int /*<<< orphan*/  center_freq1; int /*<<< orphan*/  width; } ;
struct ieee80211_csa_ie {scalar_t__ reason_code; int mode; scalar_t__ ttl; scalar_t__ pre_value; int /*<<< orphan*/  count; TYPE_8__ chandef; } ;
struct cfg80211_csa_settings {int radar_required; int block_tx; TYPE_8__ chandef; int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_19__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_20__ {TYPE_6__ hw; } ;
struct TYPE_17__ {int /*<<< orphan*/  center_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHAN_DISABLED ; 
 int /*<<< orphan*/  IEEE80211_MESH_CSA_ROLE_REPEATER ; 
 scalar_t__ IEEE80211_STA_DISABLE_40MHZ ; 
 scalar_t__ IEEE80211_STA_DISABLE_HT ; 
 scalar_t__ IEEE80211_STA_DISABLE_VHT ; 
#define  NL80211_CHAN_WIDTH_20 130 
#define  NL80211_CHAN_WIDTH_20_NOHT 129 
#define  NL80211_CHAN_WIDTH_40 128 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int WLAN_EID_CHAN_SWITCH_PARAM_TX_RESTRICT ; 
 scalar_t__ WLAN_REASON_MESH_CHAN_REGULATORY ; 
 int cfg80211_chandef_dfs_required (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ cfg80211_chandef_identical (TYPE_8__*,TYPE_11__*) ; 
 int /*<<< orphan*/  cfg80211_chandef_usable (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_reg_can_beacon (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_channel_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cfg80211_csa_settings*) ; 
 struct ieee80211_supported_band* ieee80211_get_sband (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_mesh_csa_mark_radar (struct ieee80211_sub_if_data*) ; 
 int ieee80211_parse_ch_switch_ie (struct ieee80211_sub_if_data*,struct ieee802_11_elems*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct ieee80211_csa_ie*) ; 
 int /*<<< orphan*/  mcsa_dbg (struct ieee80211_sub_if_data*,char*,...) ; 
 int /*<<< orphan*/  memset (struct cfg80211_csa_settings*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdata_assert_lock (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  sdata_info (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
ieee80211_mesh_process_chnswitch(struct ieee80211_sub_if_data *sdata,
				 struct ieee802_11_elems *elems, bool beacon)
{
	struct cfg80211_csa_settings params;
	struct ieee80211_csa_ie csa_ie;
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	struct ieee80211_supported_band *sband;
	int err;
	u32 sta_flags;

	sdata_assert_lock(sdata);

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		return false;

	sta_flags = 0;
	switch (sdata->vif.bss_conf.chandef.width) {
	case NL80211_CHAN_WIDTH_20_NOHT:
		sta_flags |= IEEE80211_STA_DISABLE_HT;
		/* fall through */
	case NL80211_CHAN_WIDTH_20:
		sta_flags |= IEEE80211_STA_DISABLE_40MHZ;
		/* fall through */
	case NL80211_CHAN_WIDTH_40:
		sta_flags |= IEEE80211_STA_DISABLE_VHT;
		break;
	default:
		break;
	}

	memset(&params, 0, sizeof(params));
	err = ieee80211_parse_ch_switch_ie(sdata, elems, sband->band,
					   sta_flags, sdata->vif.addr,
					   &csa_ie);
	if (err < 0)
		return false;
	if (err)
		return false;

	/* Mark the channel unavailable if the reason for the switch is
	 * regulatory.
	 */
	if (csa_ie.reason_code == WLAN_REASON_MESH_CHAN_REGULATORY)
		ieee80211_mesh_csa_mark_radar(sdata);

	params.chandef = csa_ie.chandef;
	params.count = csa_ie.count;

	if (!cfg80211_chandef_usable(sdata->local->hw.wiphy, &params.chandef,
				     IEEE80211_CHAN_DISABLED) ||
	    !cfg80211_reg_can_beacon(sdata->local->hw.wiphy, &params.chandef,
				     NL80211_IFTYPE_MESH_POINT)) {
		sdata_info(sdata,
			   "mesh STA %pM switches to unsupported channel (%d MHz, width:%d, CF1/2: %d/%d MHz), aborting\n",
			   sdata->vif.addr,
			   params.chandef.chan->center_freq,
			   params.chandef.width,
			   params.chandef.center_freq1,
			   params.chandef.center_freq2);
		return false;
	}

	err = cfg80211_chandef_dfs_required(sdata->local->hw.wiphy,
					    &params.chandef,
					    NL80211_IFTYPE_MESH_POINT);
	if (err < 0)
		return false;
	if (err > 0 && !ifmsh->userspace_handles_dfs) {
		sdata_info(sdata,
			   "mesh STA %pM switches to channel requiring DFS (%d MHz, width:%d, CF1/2: %d/%d MHz), aborting\n",
			   sdata->vif.addr,
			   params.chandef.chan->center_freq,
			   params.chandef.width,
			   params.chandef.center_freq1,
			   params.chandef.center_freq2);
		return false;
	}

	params.radar_required = err;

	if (cfg80211_chandef_identical(&params.chandef,
				       &sdata->vif.bss_conf.chandef)) {
		mcsa_dbg(sdata,
			 "received csa with an identical chandef, ignoring\n");
		return true;
	}

	mcsa_dbg(sdata,
		 "received channel switch announcement to go to channel %d MHz\n",
		 params.chandef.chan->center_freq);

	params.block_tx = csa_ie.mode & WLAN_EID_CHAN_SWITCH_PARAM_TX_RESTRICT;
	if (beacon) {
		ifmsh->chsw_ttl = csa_ie.ttl - 1;
		if (ifmsh->pre_value >= csa_ie.pre_value)
			return false;
		ifmsh->pre_value = csa_ie.pre_value;
	}

	if (ifmsh->chsw_ttl >= ifmsh->mshcfg.dot11MeshTTL)
		return false;

	ifmsh->csa_role = IEEE80211_MESH_CSA_ROLE_REPEATER;

	if (ieee80211_channel_switch(sdata->local->hw.wiphy, sdata->dev,
				     &params) < 0)
		return false;

	return true;
}