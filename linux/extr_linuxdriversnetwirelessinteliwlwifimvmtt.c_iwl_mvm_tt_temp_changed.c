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
typedef  scalar_t__ u32 ;
struct iwl_mvm {scalar_t__ temperature; scalar_t__ temperature_test; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_mvm_tt_handler (struct iwl_mvm*) ; 

void iwl_mvm_tt_temp_changed(struct iwl_mvm *mvm, u32 temp)
{
	/* ignore the notification if we are in test mode */
	if (mvm->temperature_test)
		return;

	if (mvm->temperature == temp)
		return;

	mvm->temperature = temp;
	iwl_mvm_tt_handler(mvm);
}