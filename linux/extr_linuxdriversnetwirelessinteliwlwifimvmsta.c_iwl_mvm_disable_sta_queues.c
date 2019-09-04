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
struct iwl_mvm_sta {TYPE_1__* tid_data; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int /*<<< orphan*/ * hw_queue; } ;
struct TYPE_2__ {scalar_t__ txq_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ IWL_MVM_INVALID_QUEUE ; 
 int /*<<< orphan*/  iwl_mvm_disable_txq (struct iwl_mvm*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int iwl_mvm_tid_to_ac_queue (int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_disable_sta_queues(struct iwl_mvm *mvm,
				       struct ieee80211_vif *vif,
				       struct iwl_mvm_sta *mvm_sta)
{
	int ac;
	int i;

	lockdep_assert_held(&mvm->mutex);

	for (i = 0; i < ARRAY_SIZE(mvm_sta->tid_data); i++) {
		if (mvm_sta->tid_data[i].txq_id == IWL_MVM_INVALID_QUEUE)
			continue;

		ac = iwl_mvm_tid_to_ac_queue(i);
		iwl_mvm_disable_txq(mvm, mvm_sta->tid_data[i].txq_id,
				    vif->hw_queue[ac], i, 0);
		mvm_sta->tid_data[i].txq_id = IWL_MVM_INVALID_QUEUE;
	}
}