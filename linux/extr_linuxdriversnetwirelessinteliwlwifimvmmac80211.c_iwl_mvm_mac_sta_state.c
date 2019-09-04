#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iwl_mvm_vif {int /*<<< orphan*/  ap_assoc_sta_count; TYPE_3__* phy_ctxt; } ;
struct iwl_mvm_sta {int sta_state; } ;
struct iwl_mvm {int last_ebs_successful; int /*<<< orphan*/  mutex; int /*<<< orphan*/  add_stream_wk; } ;
struct TYPE_4__ {int beacon_int; } ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ p2p; TYPE_1__ bss_conf; } ;
struct ieee80211_sta {scalar_t__ tdls; int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum ieee80211_sta_state { ____Placeholder_ieee80211_sta_state } ieee80211_sta_state ;
struct TYPE_6__ {TYPE_2__* channel; } ;
struct TYPE_5__ {int /*<<< orphan*/  band; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int IEEE80211_STA_ASSOC ; 
 int IEEE80211_STA_AUTH ; 
 int IEEE80211_STA_AUTHORIZED ; 
 int IEEE80211_STA_NONE ; 
 int IEEE80211_STA_NOTEXIST ; 
 int /*<<< orphan*/  IWL_DEBUG_MAC80211 (struct iwl_mvm*,char*,...) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int /*<<< orphan*/ ,int) ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_MVM_TDLS_FW_TID ; 
 scalar_t__ IWL_MVM_TDLS_STA_COUNT ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  NL80211_TDLS_DISABLE_LINK ; 
 int /*<<< orphan*/  NL80211_TDLS_ENABLE_LINK ; 
 int /*<<< orphan*/  NL80211_TDLS_SETUP ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_reserve_tid (struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_unreserve_tid (struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int iwl_mvm_add_sta (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_check_uapsd (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_disable_beacon_filter (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_enable_beacon_filter (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_mac_ctxt_changed (struct iwl_mvm*,struct ieee80211_vif*,int,int /*<<< orphan*/ *) ; 
 int iwl_mvm_phy_ctx_count (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_purge_deferred_tx_frames (struct iwl_mvm*,struct iwl_mvm_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_recalc_tdls_state (struct iwl_mvm*,struct ieee80211_vif*,int) ; 
 int iwl_mvm_rm_sta (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_rs_rate_init (struct iwl_mvm*,struct ieee80211_sta*,int /*<<< orphan*/ ,int) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_tdls_check_trigger (struct iwl_mvm*,struct ieee80211_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_tdls_sta_count (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_teardown_tdls_peers (struct iwl_mvm*) ; 
 int iwl_mvm_update_sta (struct iwl_mvm*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_mac_sta_state(struct ieee80211_hw *hw,
				 struct ieee80211_vif *vif,
				 struct ieee80211_sta *sta,
				 enum ieee80211_sta_state old_state,
				 enum ieee80211_sta_state new_state)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm_sta *mvm_sta = iwl_mvm_sta_from_mac80211(sta);
	int ret;

	IWL_DEBUG_MAC80211(mvm, "station %pM state change %d->%d\n",
			   sta->addr, old_state, new_state);

	/* this would be a mac80211 bug ... but don't crash */
	if (WARN_ON_ONCE(!mvmvif->phy_ctxt))
		return -EINVAL;

	/*
	 * If we are in a STA removal flow and in DQA mode:
	 *
	 * This is after the sync_rcu part, so the queues have already been
	 * flushed. No more TXs on their way in mac80211's path, and no more in
	 * the queues.
	 * Also, we won't be getting any new TX frames for this station.
	 * What we might have are deferred TX frames that need to be taken care
	 * of.
	 *
	 * Drop any still-queued deferred-frame before removing the STA, and
	 * make sure the worker is no longer handling frames for this STA.
	 */
	if (old_state == IEEE80211_STA_NONE &&
	    new_state == IEEE80211_STA_NOTEXIST) {
		iwl_mvm_purge_deferred_tx_frames(mvm, mvm_sta);
		flush_work(&mvm->add_stream_wk);

		/*
		 * No need to make sure deferred TX indication is off since the
		 * worker will already remove it if it was on
		 */
	}

	mutex_lock(&mvm->mutex);
	/* track whether or not the station is associated */
	mvm_sta->sta_state = new_state;

	if (old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) {
		/*
		 * Firmware bug - it'll crash if the beacon interval is less
		 * than 16. We can't avoid connecting at all, so refuse the
		 * station state change, this will cause mac80211 to abandon
		 * attempts to connect to this AP, and eventually wpa_s will
		 * blacklist the AP...
		 */
		if (vif->type == NL80211_IFTYPE_STATION &&
		    vif->bss_conf.beacon_int < 16) {
			IWL_ERR(mvm,
				"AP %pM beacon interval is %d, refusing due to firmware bug!\n",
				sta->addr, vif->bss_conf.beacon_int);
			ret = -EINVAL;
			goto out_unlock;
		}

		if (sta->tdls &&
		    (vif->p2p ||
		     iwl_mvm_tdls_sta_count(mvm, NULL) ==
						IWL_MVM_TDLS_STA_COUNT ||
		     iwl_mvm_phy_ctx_count(mvm) > 1)) {
			IWL_DEBUG_MAC80211(mvm, "refusing TDLS sta\n");
			ret = -EBUSY;
			goto out_unlock;
		}

		ret = iwl_mvm_add_sta(mvm, vif, sta);
		if (sta->tdls && ret == 0) {
			iwl_mvm_recalc_tdls_state(mvm, vif, true);
			iwl_mvm_tdls_check_trigger(mvm, vif, sta->addr,
						   NL80211_TDLS_SETUP);
		}
	} else if (old_state == IEEE80211_STA_NONE &&
		   new_state == IEEE80211_STA_AUTH) {
		/*
		 * EBS may be disabled due to previous failures reported by FW.
		 * Reset EBS status here assuming environment has been changed.
		 */
		mvm->last_ebs_successful = true;
		iwl_mvm_check_uapsd(mvm, vif, sta->addr);
		ret = 0;
	} else if (old_state == IEEE80211_STA_AUTH &&
		   new_state == IEEE80211_STA_ASSOC) {
		if (vif->type == NL80211_IFTYPE_AP) {
			mvmvif->ap_assoc_sta_count++;
			iwl_mvm_mac_ctxt_changed(mvm, vif, false, NULL);
		}

		iwl_mvm_rs_rate_init(mvm, sta, mvmvif->phy_ctxt->channel->band,
				     false);
		ret = iwl_mvm_update_sta(mvm, vif, sta);
	} else if (old_state == IEEE80211_STA_ASSOC &&
		   new_state == IEEE80211_STA_AUTHORIZED) {

		/* we don't support TDLS during DCM */
		if (iwl_mvm_phy_ctx_count(mvm) > 1)
			iwl_mvm_teardown_tdls_peers(mvm);

		if (sta->tdls)
			iwl_mvm_tdls_check_trigger(mvm, vif, sta->addr,
						   NL80211_TDLS_ENABLE_LINK);

		/* enable beacon filtering */
		WARN_ON(iwl_mvm_enable_beacon_filter(mvm, vif, 0));

		iwl_mvm_rs_rate_init(mvm, sta, mvmvif->phy_ctxt->channel->band,
				     true);

		ret = 0;
	} else if (old_state == IEEE80211_STA_AUTHORIZED &&
		   new_state == IEEE80211_STA_ASSOC) {
		/* disable beacon filtering */
		WARN_ON(iwl_mvm_disable_beacon_filter(mvm, vif, 0));
		ret = 0;
	} else if (old_state == IEEE80211_STA_ASSOC &&
		   new_state == IEEE80211_STA_AUTH) {
		if (vif->type == NL80211_IFTYPE_AP) {
			mvmvif->ap_assoc_sta_count--;
			iwl_mvm_mac_ctxt_changed(mvm, vif, false, NULL);
		}
		ret = 0;
	} else if (old_state == IEEE80211_STA_AUTH &&
		   new_state == IEEE80211_STA_NONE) {
		ret = 0;
	} else if (old_state == IEEE80211_STA_NONE &&
		   new_state == IEEE80211_STA_NOTEXIST) {
		ret = iwl_mvm_rm_sta(mvm, vif, sta);
		if (sta->tdls) {
			iwl_mvm_recalc_tdls_state(mvm, vif, false);
			iwl_mvm_tdls_check_trigger(mvm, vif, sta->addr,
						   NL80211_TDLS_DISABLE_LINK);
		}
	} else {
		ret = -EIO;
	}
 out_unlock:
	mutex_unlock(&mvm->mutex);

	if (sta->tdls && ret == 0) {
		if (old_state == IEEE80211_STA_NOTEXIST &&
		    new_state == IEEE80211_STA_NONE)
			ieee80211_reserve_tid(sta, IWL_MVM_TDLS_FW_TID);
		else if (old_state == IEEE80211_STA_NONE &&
			 new_state == IEEE80211_STA_NOTEXIST)
			ieee80211_unreserve_tid(sta, IWL_MVM_TDLS_FW_TID);
	}

	return ret;
}