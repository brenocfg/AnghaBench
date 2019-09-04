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
struct iwl_trans {int dummy; } ;
struct iwl_mvm {TYPE_1__* hw; int /*<<< orphan*/  d0i3_suspend_mutex; int /*<<< orphan*/  d0i3_suspend_flags; struct iwl_trans* trans; } ;
typedef  enum iwl_d3_status { ____Placeholder_iwl_d3_status } iwl_d3_status ;
struct TYPE_2__ {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  D0I3_DEFER_WAKEUP ; 
 int /*<<< orphan*/  D0I3_PENDING_WAKEUP ; 
 int /*<<< orphan*/  IWL_DEBUG_RPM (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int __test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _iwl_mvm_exit_d0i3 (struct iwl_mvm*) ; 
 scalar_t__ iwl_mvm_enter_d0i3_on_suspend (struct iwl_mvm*) ; 
 int iwl_mvm_exit_d0i3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_d3_resume (struct iwl_trans*,int*,int,int) ; 
 int /*<<< orphan*/  iwl_trans_resume (struct iwl_trans*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_resume_d0i3(struct iwl_mvm *mvm)
{
	bool exit_now;
	enum iwl_d3_status d3_status;
	struct iwl_trans *trans = mvm->trans;

	iwl_trans_d3_resume(trans, &d3_status, false, false);

	/*
	 * make sure to clear D0I3_DEFER_WAKEUP before
	 * calling iwl_trans_resume(), which might wait
	 * for d0i3 exit completion.
	 */
	mutex_lock(&mvm->d0i3_suspend_mutex);
	__clear_bit(D0I3_DEFER_WAKEUP, &mvm->d0i3_suspend_flags);
	exit_now = __test_and_clear_bit(D0I3_PENDING_WAKEUP,
					&mvm->d0i3_suspend_flags);
	mutex_unlock(&mvm->d0i3_suspend_mutex);
	if (exit_now) {
		IWL_DEBUG_RPM(mvm, "Run deferred d0i3 exit\n");
		_iwl_mvm_exit_d0i3(mvm);
	}

	iwl_trans_resume(trans);

	if (iwl_mvm_enter_d0i3_on_suspend(mvm)) {
		int ret = iwl_mvm_exit_d0i3(mvm->hw->priv);

		if (ret)
			return ret;
		/*
		 * d0i3 exit will be deferred until reconfig_complete.
		 * make sure there we are out of d0i3.
		 */
	}
	return 0;
}