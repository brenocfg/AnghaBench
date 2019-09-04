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

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_D0I3 ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 scalar_t__ iwl_mvm_enter_d0i3_on_suspend (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_is_d0i3_supported (struct iwl_mvm*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_resume_complete(struct iwl_mvm *mvm)
{
	if (iwl_mvm_is_d0i3_supported(mvm) &&
	    iwl_mvm_enter_d0i3_on_suspend(mvm))
		WARN_ONCE(!wait_event_timeout(mvm->d0i3_exit_waitq,
					      !test_bit(IWL_MVM_STATUS_IN_D0I3,
							&mvm->status),
					      HZ),
			  "D0i3 exit on resume timed out\n");
}