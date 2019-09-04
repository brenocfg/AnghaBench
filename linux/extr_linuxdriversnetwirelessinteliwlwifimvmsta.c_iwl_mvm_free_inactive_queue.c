#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct iwl_mvm_sta {TYPE_1__* vif; } ;
struct iwl_mvm {int /*<<< orphan*/  queue_info_lock; TYPE_2__* queue_info; int /*<<< orphan*/  mutex; } ;
struct TYPE_4__ {size_t mac80211_ac; size_t ra_sta_id; size_t txq_tid; int /*<<< orphan*/  status; } ;
struct TYPE_3__ {int /*<<< orphan*/ * hw_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*,int,int) ; 
 int /*<<< orphan*/  IWL_MVM_QUEUE_INACTIVE ; 
 scalar_t__ WARN_ON (int) ; 
 int iwl_mvm_disable_txq (struct iwl_mvm*,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int iwl_mvm_has_new_tx_api (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_invalidate_sta_queue (struct iwl_mvm*,int,unsigned long,int) ; 
 unsigned long iwl_mvm_remove_sta_queue_marking (struct iwl_mvm*,int) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_staid_protected (struct iwl_mvm*,size_t) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_free_inactive_queue(struct iwl_mvm *mvm, int queue,
				       bool same_sta)
{
	struct iwl_mvm_sta *mvmsta;
	u8 txq_curr_ac, sta_id, tid;
	unsigned long disable_agg_tids = 0;
	int ret;

	lockdep_assert_held(&mvm->mutex);

	if (WARN_ON(iwl_mvm_has_new_tx_api(mvm)))
		return -EINVAL;

	spin_lock_bh(&mvm->queue_info_lock);
	txq_curr_ac = mvm->queue_info[queue].mac80211_ac;
	sta_id = mvm->queue_info[queue].ra_sta_id;
	tid = mvm->queue_info[queue].txq_tid;
	spin_unlock_bh(&mvm->queue_info_lock);

	mvmsta = iwl_mvm_sta_from_staid_protected(mvm, sta_id);
	if (WARN_ON(!mvmsta))
		return -EINVAL;

	disable_agg_tids = iwl_mvm_remove_sta_queue_marking(mvm, queue);
	/* Disable the queue */
	if (disable_agg_tids)
		iwl_mvm_invalidate_sta_queue(mvm, queue,
					     disable_agg_tids, false);

	ret = iwl_mvm_disable_txq(mvm, queue,
				  mvmsta->vif->hw_queue[txq_curr_ac],
				  tid, 0);
	if (ret) {
		/* Re-mark the inactive queue as inactive */
		spin_lock_bh(&mvm->queue_info_lock);
		mvm->queue_info[queue].status = IWL_MVM_QUEUE_INACTIVE;
		spin_unlock_bh(&mvm->queue_info_lock);
		IWL_ERR(mvm,
			"Failed to free inactive queue %d (ret=%d)\n",
			queue, ret);

		return ret;
	}

	/* If TXQ is allocated to another STA, update removal in FW */
	if (!same_sta)
		iwl_mvm_invalidate_sta_queue(mvm, queue, 0, true);

	return 0;
}