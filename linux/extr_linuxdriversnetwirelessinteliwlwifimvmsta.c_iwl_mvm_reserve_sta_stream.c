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
struct iwl_mvm_sta {scalar_t__ sta_id; int reserved_queue; } ;
struct iwl_mvm {int /*<<< orphan*/  queue_info_lock; TYPE_1__* queue_info; } ;
struct ieee80211_sta {int /*<<< orphan*/  tdls; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_2__ {scalar_t__ status; scalar_t__ ra_sta_id; int /*<<< orphan*/  hw_queue_refcount; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 size_t IWL_MVM_DQA_BSS_CLIENT_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_DQA_MAX_DATA_QUEUE ; 
 int /*<<< orphan*/  IWL_MVM_DQA_MIN_DATA_QUEUE ; 
 scalar_t__ IWL_MVM_QUEUE_FREE ; 
 scalar_t__ IWL_MVM_QUEUE_INACTIVE ; 
 scalar_t__ IWL_MVM_QUEUE_RESERVED ; 
 int NL80211_IFTYPE_STATION ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int iwl_mvm_find_free_queue (struct iwl_mvm*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_free_inactive_queue (struct iwl_mvm*,int,int) ; 
 int /*<<< orphan*/  iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_inactivity_check (struct iwl_mvm*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_reserve_sta_stream(struct iwl_mvm *mvm,
				      struct ieee80211_sta *sta,
				      enum nl80211_iftype vif_type)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	int queue;
	bool using_inactive_queue = false, same_sta = false;

	/* queue reserving is disabled on new TX path */
	if (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		return 0;

	/*
	 * Check for inactive queues, so we don't reach a situation where we
	 * can't add a STA due to a shortage in queues that doesn't really exist
	 */
	iwl_mvm_inactivity_check(mvm);

	spin_lock_bh(&mvm->queue_info_lock);

	/* Make sure we have free resources for this STA */
	if (vif_type == NL80211_IFTYPE_STATION && !sta->tdls &&
	    !mvm->queue_info[IWL_MVM_DQA_BSS_CLIENT_QUEUE].hw_queue_refcount &&
	    (mvm->queue_info[IWL_MVM_DQA_BSS_CLIENT_QUEUE].status ==
	     IWL_MVM_QUEUE_FREE))
		queue = IWL_MVM_DQA_BSS_CLIENT_QUEUE;
	else
		queue = iwl_mvm_find_free_queue(mvm, mvmsta->sta_id,
						IWL_MVM_DQA_MIN_DATA_QUEUE,
						IWL_MVM_DQA_MAX_DATA_QUEUE);
	if (queue < 0) {
		spin_unlock_bh(&mvm->queue_info_lock);
		IWL_ERR(mvm, "No available queues for new station\n");
		return -ENOSPC;
	} else if (mvm->queue_info[queue].status == IWL_MVM_QUEUE_INACTIVE) {
		/*
		 * If this queue is already allocated but inactive we'll need to
		 * first free this queue before enabling it again, we'll mark
		 * it as reserved to make sure no new traffic arrives on it
		 */
		using_inactive_queue = true;
		same_sta = mvm->queue_info[queue].ra_sta_id == mvmsta->sta_id;
	}
	mvm->queue_info[queue].status = IWL_MVM_QUEUE_RESERVED;

	spin_unlock_bh(&mvm->queue_info_lock);

	mvmsta->reserved_queue = queue;

	if (using_inactive_queue)
		iwl_mvm_free_inactive_queue(mvm, queue, same_sta);

	IWL_DEBUG_TX_QUEUES(mvm, "Reserving data queue #%d for sta_id %d\n",
			    queue, mvmsta->sta_id);

	return 0;
}