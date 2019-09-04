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
struct iwl_mvm {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_HW_CTKILL ; 
 int /*<<< orphan*/  iwl_mvm_set_hw_ctkill_state (struct iwl_mvm*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_exit_ctkill(struct iwl_mvm *mvm)
{
	if (!test_bit(IWL_MVM_STATUS_HW_CTKILL, &mvm->status))
		return;

	IWL_ERR(mvm, "Exit CT Kill\n");
	iwl_mvm_set_hw_ctkill_state(mvm, false);
}