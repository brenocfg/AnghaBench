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
struct iwl_op_mode {int dummy; } ;
struct TYPE_2__ {scalar_t__ cur_fw_img; } ;
struct iwl_mvm {TYPE_1__ fwrt; int /*<<< orphan*/  notif_wait; int /*<<< orphan*/  status; int /*<<< orphan*/  calibrating; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_MVM_STATUS_HW_RFKILL ; 
 struct iwl_mvm* IWL_OP_MODE_GET_MVM (struct iwl_op_mode*) ; 
 scalar_t__ IWL_UCODE_INIT ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_abort_notification_waits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_mvm_set_rfkill_state (struct iwl_mvm*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool iwl_mvm_set_hw_rfkill_state(struct iwl_op_mode *op_mode, bool state)
{
	struct iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	bool calibrating = READ_ONCE(mvm->calibrating);

	if (state)
		set_bit(IWL_MVM_STATUS_HW_RFKILL, &mvm->status);
	else
		clear_bit(IWL_MVM_STATUS_HW_RFKILL, &mvm->status);

	iwl_mvm_set_rfkill_state(mvm);

	/* iwl_run_init_mvm_ucode is waiting for results, abort it */
	if (calibrating)
		iwl_abort_notification_waits(&mvm->notif_wait);

	/*
	 * Stop the device if we run OPERATIONAL firmware or if we are in the
	 * middle of the calibrations.
	 */
	return state && (mvm->fwrt.cur_fw_img != IWL_UCODE_INIT || calibrating);
}