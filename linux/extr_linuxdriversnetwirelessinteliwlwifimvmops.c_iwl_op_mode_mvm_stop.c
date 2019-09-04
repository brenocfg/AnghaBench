#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwl_op_mode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  work; } ;
struct iwl_mvm {int init_status; int /*<<< orphan*/  hw; int /*<<< orphan*/  d0i3_suspend_mutex; int /*<<< orphan*/  mutex; TYPE_2__ tcm; TYPE_1__* nvm_sections; int /*<<< orphan*/ * nvm_data; int /*<<< orphan*/ * phy_db; int /*<<< orphan*/  trans; int /*<<< orphan*/ * mcast_filter_cmd; int /*<<< orphan*/ * scan_cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int IWL_MVM_INIT_STATUS_REG_HW_INIT_COMPLETE ; 
 struct iwl_mvm* IWL_OP_MODE_GET_MVM (struct iwl_op_mode*) ; 
 int NVM_MAX_NUM_SECTIONS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (int /*<<< orphan*/ ) ; 
 scalar_t__ iwl_mvm_is_d0i3_supported (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_leds_exit (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_thermal_exit (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_mvm_tof_clean (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_phy_db_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_trans_op_mode_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_trans_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_op_mode_mvm_stop(struct iwl_op_mode *op_mode)
{
	struct iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	int i;

	/* If d0i3 is supported, we have released the reference that
	 * the transport started with, so we should take it back now
	 * that we are leaving.
	 */
	if (iwl_mvm_is_d0i3_supported(mvm))
		iwl_trans_ref(mvm->trans);

	iwl_mvm_leds_exit(mvm);

	iwl_mvm_thermal_exit(mvm);

	if (mvm->init_status & IWL_MVM_INIT_STATUS_REG_HW_INIT_COMPLETE) {
		ieee80211_unregister_hw(mvm->hw);
		mvm->init_status &= ~IWL_MVM_INIT_STATUS_REG_HW_INIT_COMPLETE;
	}

	kfree(mvm->scan_cmd);
	kfree(mvm->mcast_filter_cmd);
	mvm->mcast_filter_cmd = NULL;

#if defined(CONFIG_PM_SLEEP) && defined(CONFIG_IWLWIFI_DEBUGFS)
	kfree(mvm->d3_resume_sram);
#endif
	iwl_trans_op_mode_leave(mvm->trans);

	iwl_phy_db_free(mvm->phy_db);
	mvm->phy_db = NULL;

	kfree(mvm->nvm_data);
	for (i = 0; i < NVM_MAX_NUM_SECTIONS; i++)
		kfree(mvm->nvm_sections[i].data);

	cancel_delayed_work_sync(&mvm->tcm.work);

	iwl_mvm_tof_clean(mvm);

	mutex_destroy(&mvm->mutex);
	mutex_destroy(&mvm->d0i3_suspend_mutex);

	ieee80211_free_hw(mvm->hw);
}