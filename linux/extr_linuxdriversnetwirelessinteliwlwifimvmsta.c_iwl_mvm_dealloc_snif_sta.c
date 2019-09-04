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
struct iwl_mvm {int /*<<< orphan*/  snif_sta; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_mvm_dealloc_int_sta (struct iwl_mvm*,int /*<<< orphan*/ *) ; 

void iwl_mvm_dealloc_snif_sta(struct iwl_mvm *mvm)
{
	iwl_mvm_dealloc_int_sta(mvm, &mvm->snif_sta);
}