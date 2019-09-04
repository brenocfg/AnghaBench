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
struct iwl_trans {int /*<<< orphan*/  system_pm_mode; } ;
struct iwl_mvm {int /*<<< orphan*/  d0i3_suspend_mutex; int /*<<< orphan*/  d0i3_suspend_flags; int /*<<< orphan*/  fwrt; int /*<<< orphan*/  d0i3_exit_work; struct iwl_trans* trans; } ;
struct ieee80211_hw {int dummy; } ;
struct cfg80211_wowlan {scalar_t__ any; } ;

/* Variables and functions */
 int /*<<< orphan*/  D0I3_DEFER_WAKEUP ; 
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  IWL_PLAT_PM_MODE_D0I3 ; 
 int /*<<< orphan*/  IWL_PLAT_PM_MODE_D3 ; 
 int __iwl_mvm_suspend (struct ieee80211_hw*,struct cfg80211_wowlan*,int) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_fw_runtime_suspend (int /*<<< orphan*/ *) ; 
 scalar_t__ iwl_mvm_enter_d0i3_on_suspend (struct iwl_mvm*) ; 
 int iwl_mvm_enter_d0i3_sync (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_pause_tcm (struct iwl_mvm*,int) ; 
 int /*<<< orphan*/  iwl_trans_d3_suspend (struct iwl_trans*,int,int) ; 
 int iwl_trans_suspend (struct iwl_trans*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int iwl_mvm_suspend(struct ieee80211_hw *hw, struct cfg80211_wowlan *wowlan)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	struct iwl_trans *trans = mvm->trans;
	int ret;

	/* make sure the d0i3 exit work is not pending */
	flush_work(&mvm->d0i3_exit_work);
	iwl_mvm_pause_tcm(mvm, true);

	iwl_fw_runtime_suspend(&mvm->fwrt);

	ret = iwl_trans_suspend(trans);
	if (ret)
		return ret;

	if (wowlan->any) {
		trans->system_pm_mode = IWL_PLAT_PM_MODE_D0I3;

		if (iwl_mvm_enter_d0i3_on_suspend(mvm)) {
			ret = iwl_mvm_enter_d0i3_sync(mvm);

			if (ret)
				return ret;
		}

		mutex_lock(&mvm->d0i3_suspend_mutex);
		__set_bit(D0I3_DEFER_WAKEUP, &mvm->d0i3_suspend_flags);
		mutex_unlock(&mvm->d0i3_suspend_mutex);

		iwl_trans_d3_suspend(trans, false, false);

		return 0;
	}

	trans->system_pm_mode = IWL_PLAT_PM_MODE_D3;

	return __iwl_mvm_suspend(hw, wowlan, false);
}