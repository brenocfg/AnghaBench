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
struct iwl_mvm {int* refs; int /*<<< orphan*/  refs_lock; int /*<<< orphan*/  trans; } ;
typedef  enum iwl_mvm_ref_type { ____Placeholder_iwl_mvm_ref_type } iwl_mvm_ref_type ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RPM (struct iwl_mvm*,char*,int,int) ; 
 int IWL_MVM_REF_COUNT ; 
 int /*<<< orphan*/  iwl_mvm_is_d0i3_supported (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_trans_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_unref_all_except(struct iwl_mvm *mvm,
				     enum iwl_mvm_ref_type except_ref)
{
	int i, j;

	if (!iwl_mvm_is_d0i3_supported(mvm))
		return;

	spin_lock_bh(&mvm->refs_lock);
	for (i = 0; i < IWL_MVM_REF_COUNT; i++) {
		if (except_ref == i || !mvm->refs[i])
			continue;

		IWL_DEBUG_RPM(mvm, "Cleanup: remove mvm ref type %d (%d)\n",
			      i, mvm->refs[i]);
		for (j = 0; j < mvm->refs[i]; j++)
			iwl_trans_unref(mvm->trans);
		mvm->refs[i] = 0;
	}
	spin_unlock_bh(&mvm->refs_lock);
}