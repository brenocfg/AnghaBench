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
struct iwl_mvm_sta {int dummy; } ;
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RATE (struct iwl_mvm*,char*) ; 

int rs_fw_tx_protection(struct iwl_mvm *mvm, struct iwl_mvm_sta *mvmsta,
			bool enable)
{
	/* TODO: need to introduce a new FW cmd since LQ cmd is not relevant */
	IWL_DEBUG_RATE(mvm, "tx protection - not implemented yet.\n");
	return 0;
}