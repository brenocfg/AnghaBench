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
struct iwl_mvm {scalar_t__* error_event_table; TYPE_1__* trans; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  STATUS_DEVICE_ENABLED ; 
 int /*<<< orphan*/  iwl_mvm_dump_lmac_error_log (struct iwl_mvm*,scalar_t__) ; 
 int /*<<< orphan*/  iwl_mvm_dump_umac_error_log (struct iwl_mvm*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void iwl_mvm_dump_nic_error_log(struct iwl_mvm *mvm)
{
	if (!test_bit(STATUS_DEVICE_ENABLED, &mvm->trans->status)) {
		IWL_ERR(mvm,
			"DEVICE_ENABLED bit is not set. Aborting dump.\n");
		return;
	}

	iwl_mvm_dump_lmac_error_log(mvm, mvm->error_event_table[0]);

	if (mvm->error_event_table[1])
		iwl_mvm_dump_lmac_error_log(mvm, mvm->error_event_table[1]);

	iwl_mvm_dump_umac_error_log(mvm);
}