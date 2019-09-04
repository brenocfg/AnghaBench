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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ cur_fw_img; } ;
struct iwl_mvm {int /*<<< orphan*/  d0i3_exit_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  d0i3_suspend_mutex; int /*<<< orphan*/  d0i3_suspend_flags; TYPE_1__ fwrt; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int CMD_HIGH_PRIO ; 
 int CMD_SEND_IN_IDLE ; 
 int CMD_WAKE_UP_TRANS ; 
 int /*<<< orphan*/  D0I3_DEFER_WAKEUP ; 
 int /*<<< orphan*/  D0I3_END_CMD ; 
 int /*<<< orphan*/  D0I3_PENDING_WAKEUP ; 
 int EINVAL ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 int /*<<< orphan*/  IWL_DEBUG_RPM (struct iwl_mvm*,char*) ; 
 scalar_t__ IWL_UCODE_REGULAR ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_exit_d0i3_iterator ; 
 int iwl_mvm_send_cmd_pdu (struct iwl_mvm*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int _iwl_mvm_exit_d0i3(struct iwl_mvm *mvm)
{
	u32 flags = CMD_ASYNC | CMD_HIGH_PRIO | CMD_SEND_IN_IDLE |
		    CMD_WAKE_UP_TRANS;
	int ret;

	IWL_DEBUG_RPM(mvm, "MVM exiting D0i3\n");

	if (WARN_ON_ONCE(mvm->fwrt.cur_fw_img != IWL_UCODE_REGULAR))
		return -EINVAL;

	mutex_lock(&mvm->d0i3_suspend_mutex);
	if (test_bit(D0I3_DEFER_WAKEUP, &mvm->d0i3_suspend_flags)) {
		IWL_DEBUG_RPM(mvm, "Deferring d0i3 exit until resume\n");
		__set_bit(D0I3_PENDING_WAKEUP, &mvm->d0i3_suspend_flags);
		mutex_unlock(&mvm->d0i3_suspend_mutex);
		return 0;
	}
	mutex_unlock(&mvm->d0i3_suspend_mutex);

	ret = iwl_mvm_send_cmd_pdu(mvm, D0I3_END_CMD, flags, 0, NULL);
	if (ret)
		goto out;

	ieee80211_iterate_active_interfaces_atomic(mvm->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   iwl_mvm_exit_d0i3_iterator,
						   mvm);
out:
	schedule_work(&mvm->d0i3_exit_work);
	return ret;
}