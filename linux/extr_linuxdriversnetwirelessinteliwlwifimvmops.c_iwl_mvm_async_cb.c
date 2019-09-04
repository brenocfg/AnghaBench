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
struct iwl_mvm {int /*<<< orphan*/  trans; } ;
struct iwl_device_cmd {int dummy; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_OP_MODE_GET_MVM (struct iwl_op_mode*) ; 
 int /*<<< orphan*/  iwl_trans_block_txq_ptrs (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iwl_mvm_async_cb(struct iwl_op_mode *op_mode,
			     const struct iwl_device_cmd *cmd)
{
	struct iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);

	/*
	 * For now, we only set the CMD_WANT_ASYNC_CALLBACK for ADD_STA
	 * commands that need to block the Tx queues.
	 */
	iwl_trans_block_txq_ptrs(mvm->trans, false);
}