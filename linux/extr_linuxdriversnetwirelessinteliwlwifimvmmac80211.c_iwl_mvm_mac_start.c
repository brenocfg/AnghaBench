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
struct iwl_mvm {int /*<<< orphan*/  mutex; int /*<<< orphan*/  status; int /*<<< orphan*/  d0i3_exit_waitq; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_D0I3 ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 int __iwl_mvm_mac_start (struct iwl_mvm*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iwl_mvm_mac_start(struct ieee80211_hw *hw)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	int ret;

	/* Some hw restart cleanups must not hold the mutex */
	if (test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)) {
		/*
		 * Make sure we are out of d0i3. This is needed
		 * to make sure the reference accounting is correct
		 * (and there is no stale d0i3_exit_work).
		 */
		wait_event_timeout(mvm->d0i3_exit_waitq,
				   !test_bit(IWL_MVM_STATUS_IN_D0I3,
					     &mvm->status),
				   HZ);
	}

	mutex_lock(&mvm->mutex);
	ret = __iwl_mvm_mac_start(mvm);
	mutex_unlock(&mvm->mutex);

	return ret;
}