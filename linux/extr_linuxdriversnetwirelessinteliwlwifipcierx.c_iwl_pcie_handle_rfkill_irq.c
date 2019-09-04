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
struct isr_statistics {int /*<<< orphan*/  rfkill; } ;
struct iwl_trans_pcie {scalar_t__ opmode_down; int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  mutex; struct isr_statistics isr_stats; } ;
struct iwl_trans {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_RF_KILL (struct iwl_trans*,char*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  IWL_WARN (struct iwl_trans*,char*,char*) ; 
 int /*<<< orphan*/  STATUS_RFKILL_HW ; 
 int /*<<< orphan*/  STATUS_RFKILL_OPMODE ; 
 int /*<<< orphan*/  STATUS_SYNC_HCMD_ACTIVE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int iwl_is_rfkill_set (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_trans_pcie_rf_kill (struct iwl_trans*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void iwl_pcie_handle_rfkill_irq(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct isr_statistics *isr_stats = &trans_pcie->isr_stats;
	bool hw_rfkill, prev, report;

	mutex_lock(&trans_pcie->mutex);
	prev = test_bit(STATUS_RFKILL_OPMODE, &trans->status);
	hw_rfkill = iwl_is_rfkill_set(trans);
	if (hw_rfkill) {
		set_bit(STATUS_RFKILL_OPMODE, &trans->status);
		set_bit(STATUS_RFKILL_HW, &trans->status);
	}
	if (trans_pcie->opmode_down)
		report = hw_rfkill;
	else
		report = test_bit(STATUS_RFKILL_OPMODE, &trans->status);

	IWL_WARN(trans, "RF_KILL bit toggled to %s.\n",
		 hw_rfkill ? "disable radio" : "enable radio");

	isr_stats->rfkill++;

	if (prev != report)
		iwl_trans_pcie_rf_kill(trans, report);
	mutex_unlock(&trans_pcie->mutex);

	if (hw_rfkill) {
		if (test_and_clear_bit(STATUS_SYNC_HCMD_ACTIVE,
				       &trans->status))
			IWL_DEBUG_RF_KILL(trans,
					  "Rfkill while SYNC HCMD in flight\n");
		wake_up(&trans_pcie->wait_command_queue);
	} else {
		clear_bit(STATUS_RFKILL_HW, &trans->status);
		if (trans_pcie->opmode_down)
			clear_bit(STATUS_RFKILL_OPMODE, &trans->status);
	}
}