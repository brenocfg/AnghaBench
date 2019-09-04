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
struct iwl_mvm {int /*<<< orphan*/  trans; int /*<<< orphan*/  fwrt; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_STATUS_FIRMWARE_RUNNING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_free_fw_paging (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_fw_cancel_timestamp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_fw_dump_conf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_trans_stop_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void iwl_mvm_stop_device(struct iwl_mvm *mvm)
{
	iwl_fw_cancel_timestamp(&mvm->fwrt);
	iwl_free_fw_paging(&mvm->fwrt);
	clear_bit(IWL_MVM_STATUS_FIRMWARE_RUNNING, &mvm->status);
	iwl_fw_dump_conf_clear(&mvm->fwrt);
	iwl_trans_stop_device(mvm->trans);
}