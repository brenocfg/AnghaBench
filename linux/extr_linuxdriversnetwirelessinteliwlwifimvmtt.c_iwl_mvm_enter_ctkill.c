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
typedef  int u32 ;
struct TYPE_2__ {int ct_kill_duration; } ;
struct iwl_mvm_tt_mgmt {int throttle; int dynamic_smps; int /*<<< orphan*/  ct_kill_exit; TYPE_1__ params; } ;
struct iwl_mvm {int /*<<< orphan*/  temperature_test; int /*<<< orphan*/  status; struct iwl_mvm_tt_mgmt thermal_throttle; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_HW_CTKILL ; 
 int /*<<< orphan*/  iwl_mvm_is_tt_in_fw (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_set_hw_ctkill_state (struct iwl_mvm*,int) ; 
 int /*<<< orphan*/  round_jiffies_relative (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void iwl_mvm_enter_ctkill(struct iwl_mvm *mvm)
{
	struct iwl_mvm_tt_mgmt *tt = &mvm->thermal_throttle;
	u32 duration = tt->params.ct_kill_duration;

	if (test_bit(IWL_MVM_STATUS_HW_CTKILL, &mvm->status))
		return;

	IWL_ERR(mvm, "Enter CT Kill\n");
	iwl_mvm_set_hw_ctkill_state(mvm, true);

	if (!iwl_mvm_is_tt_in_fw(mvm)) {
		tt->throttle = false;
		tt->dynamic_smps = false;
	}

	/* Don't schedule an exit work if we're in test mode, since
	 * the temperature will not change unless we manually set it
	 * again (or disable testing).
	 */
	if (!mvm->temperature_test)
		schedule_delayed_work(&tt->ct_kill_exit,
				      round_jiffies_relative(duration * HZ));
}