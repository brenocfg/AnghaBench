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
struct iwl_mvm {int /*<<< orphan*/  fwrt; TYPE_1__* trans; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ system_pm_mode; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_MAC80211_GET_MVM (struct ieee80211_hw*) ; 
 scalar_t__ IWL_PLAT_PM_MODE_D0I3 ; 
 scalar_t__ IWL_PLAT_PM_MODE_DISABLED ; 
 int /*<<< orphan*/  iwl_fw_runtime_resume (int /*<<< orphan*/ *) ; 
 int iwl_mvm_resume_d0i3 (struct iwl_mvm*) ; 
 int iwl_mvm_resume_d3 (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_resume_tcm (struct iwl_mvm*) ; 

int iwl_mvm_resume(struct ieee80211_hw *hw)
{
	struct iwl_mvm *mvm = IWL_MAC80211_GET_MVM(hw);
	int ret;

	if (mvm->trans->system_pm_mode == IWL_PLAT_PM_MODE_D0I3)
		ret = iwl_mvm_resume_d0i3(mvm);
	else
		ret = iwl_mvm_resume_d3(mvm);

	mvm->trans->system_pm_mode = IWL_PLAT_PM_MODE_DISABLED;

	iwl_mvm_resume_tcm(mvm);

	iwl_fw_runtime_resume(&mvm->fwrt);

	return ret;
}