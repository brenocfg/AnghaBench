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
struct iwl_mvm {int /*<<< orphan*/  trans; int /*<<< orphan*/  refs_lock; int /*<<< orphan*/ * refs; } ;
typedef  enum iwl_mvm_ref_type { ____Placeholder_iwl_mvm_ref_type } iwl_mvm_ref_type ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RPM (struct iwl_mvm*,char*,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iwl_mvm_is_d0i3_supported (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_trans_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iwl_mvm_unref(struct iwl_mvm *mvm, enum iwl_mvm_ref_type ref_type)
{
	if (!iwl_mvm_is_d0i3_supported(mvm))
		return;

	IWL_DEBUG_RPM(mvm, "Leave mvm reference - type %d\n", ref_type);
	spin_lock_bh(&mvm->refs_lock);
	if (WARN_ON(!mvm->refs[ref_type])) {
		spin_unlock_bh(&mvm->refs_lock);
		return;
	}
	mvm->refs[ref_type]--;
	spin_unlock_bh(&mvm->refs_lock);
	iwl_trans_unref(mvm->trans);
}