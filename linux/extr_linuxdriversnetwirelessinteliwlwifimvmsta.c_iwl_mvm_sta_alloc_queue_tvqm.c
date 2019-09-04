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
struct iwl_mvm_sta {int /*<<< orphan*/  lock; TYPE_1__* tid_data; int /*<<< orphan*/  sta_id; TYPE_2__* vif; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_4__ {size_t* hw_queue; } ;
struct TYPE_3__ {int txq_id; int is_tid_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TX_QUEUES (struct iwl_mvm*,char*,int,...) ; 
 unsigned int iwl_mvm_get_wd_timeout (struct iwl_mvm*,TYPE_2__*,int,int) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int iwl_mvm_tvqm_enable_txq (struct iwl_mvm*,size_t,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_sta_alloc_queue_tvqm(struct iwl_mvm *mvm,
					struct ieee80211_sta *sta, u8 ac,
					int tid)
{
	struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
	unsigned int wdg_timeout =
		iwl_mvm_get_wd_timeout(mvm, mvmsta->vif, false, false);
	u8 mac_queue = mvmsta->vif->hw_queue[ac];
	int queue = -1;

	lockdep_assert_held(&mvm->mutex);

	IWL_DEBUG_TX_QUEUES(mvm,
			    "Allocating queue for sta %d on tid %d\n",
			    mvmsta->sta_id, tid);
	queue = iwl_mvm_tvqm_enable_txq(mvm, mac_queue, mvmsta->sta_id, tid,
					wdg_timeout);
	if (queue < 0)
		return queue;

	IWL_DEBUG_TX_QUEUES(mvm, "Allocated queue is %d\n", queue);

	spin_lock_bh(&mvmsta->lock);
	mvmsta->tid_data[tid].txq_id = queue;
	mvmsta->tid_data[tid].is_tid_active = true;
	spin_unlock_bh(&mvmsta->lock);

	return 0;
}