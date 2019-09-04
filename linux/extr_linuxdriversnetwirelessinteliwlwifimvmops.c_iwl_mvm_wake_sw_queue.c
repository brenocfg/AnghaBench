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
struct iwl_op_mode {int dummy; } ;
struct iwl_mvm {unsigned long* hw_queue_to_mac80211; int /*<<< orphan*/  queue_info_lock; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_OP_MODE_GET_MVM (struct iwl_op_mode*) ; 
 int /*<<< orphan*/  iwl_mvm_start_mac_queues (struct iwl_mvm*,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_wake_sw_queue(struct iwl_op_mode *op_mode, int hw_queue)
{
	struct iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	unsigned long mq;

	spin_lock_bh(&mvm->queue_info_lock);
	mq = mvm->hw_queue_to_mac80211[hw_queue];
	spin_unlock_bh(&mvm->queue_info_lock);

	iwl_mvm_start_mac_queues(mvm, mq);
}