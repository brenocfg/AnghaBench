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
struct iwl_mvm {int /*<<< orphan*/  refs_lock; scalar_t__* refs; } ;

/* Variables and functions */
 int IWL_MVM_REF_COUNT ; 
 int /*<<< orphan*/  iwl_mvm_is_d0i3_supported (struct iwl_mvm*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

bool iwl_mvm_ref_taken(struct iwl_mvm *mvm)
{
	int i;
	bool taken = false;

	if (!iwl_mvm_is_d0i3_supported(mvm))
		return true;

	spin_lock_bh(&mvm->refs_lock);
	for (i = 0; i < IWL_MVM_REF_COUNT; i++) {
		if (mvm->refs[i]) {
			taken = true;
			break;
		}
	}
	spin_unlock_bh(&mvm->refs_lock);

	return taken;
}