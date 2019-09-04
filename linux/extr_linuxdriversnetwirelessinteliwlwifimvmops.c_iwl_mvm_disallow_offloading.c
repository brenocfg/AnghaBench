#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct iwl_mvm_vif {scalar_t__ ap_sta_id; } ;
struct iwl_mvm_tid_data {scalar_t__ state; } ;
struct iwl_mvm_sta {int /*<<< orphan*/  lock; struct iwl_mvm_tid_data* tid_data; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_d0i3_iter_data {scalar_t__ offloading_tid; } ;
struct ieee80211_vif {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t) ; 
 scalar_t__ IWL_AGG_OFF ; 
 size_t IWL_MAX_TID_COUNT ; 
 scalar_t__ IWL_MVM_INVALID_STA ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ ffs (int /*<<< orphan*/ ) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_staid_rcu (struct iwl_mvm*,scalar_t__) ; 
 scalar_t__ iwl_mvm_tid_queued (struct iwl_mvm*,struct iwl_mvm_tid_data*) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool iwl_mvm_disallow_offloading(struct iwl_mvm *mvm,
					struct ieee80211_vif *vif,
					struct iwl_d0i3_iter_data *iter_data)
{
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	struct iwl_mvm_sta *mvmsta;
	u32 available_tids = 0;
	u8 tid;

	if (WARN_ON(vif->type != NL80211_IFTYPE_STATION ||
		    mvmvif->ap_sta_id == IWL_MVM_INVALID_STA))
		return false;

	mvmsta = iwl_mvm_sta_from_staid_rcu(mvm, mvmvif->ap_sta_id);
	if (!mvmsta)
		return false;

	spin_lock_bh(&mvmsta->lock);
	for (tid = 0; tid < IWL_MAX_TID_COUNT; tid++) {
		struct iwl_mvm_tid_data *tid_data = &mvmsta->tid_data[tid];

		/*
		 * in case of pending tx packets, don't use this tid
		 * for offloading in order to prevent reuse of the same
		 * qos seq counters.
		 */
		if (iwl_mvm_tid_queued(mvm, tid_data))
			continue;

		if (tid_data->state != IWL_AGG_OFF)
			continue;

		available_tids |= BIT(tid);
	}
	spin_unlock_bh(&mvmsta->lock);

	/*
	 * disallow protocol offloading if we have no available tid
	 * (with no pending frames and no active aggregation,
	 * as we don't handle "holes" properly - the scheduler needs the
	 * frame's seq number and TFD index to match)
	 */
	if (!available_tids)
		return true;

	/* for simplicity, just use the first available tid */
	iter_data->offloading_tid = ffs(available_tids) - 1;
	return false;
}