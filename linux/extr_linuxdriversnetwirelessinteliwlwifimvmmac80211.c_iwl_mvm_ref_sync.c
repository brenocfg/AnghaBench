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
struct iwl_mvm {int /*<<< orphan*/  status; int /*<<< orphan*/  d0i3_exit_waitq; } ;
typedef  enum iwl_mvm_ref_type { ____Placeholder_iwl_mvm_ref_type } iwl_mvm_ref_type ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_D0I3 ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iwl_mvm_ref (struct iwl_mvm*,int) ; 
 int /*<<< orphan*/  iwl_mvm_unref (struct iwl_mvm*,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int iwl_mvm_ref_sync(struct iwl_mvm *mvm, enum iwl_mvm_ref_type ref_type)
{
	iwl_mvm_ref(mvm, ref_type);

	if (!wait_event_timeout(mvm->d0i3_exit_waitq,
				!test_bit(IWL_MVM_STATUS_IN_D0I3, &mvm->status),
				HZ)) {
		WARN_ON_ONCE(1);
		iwl_mvm_unref(mvm, ref_type);
		return -EIO;
	}

	return 0;
}