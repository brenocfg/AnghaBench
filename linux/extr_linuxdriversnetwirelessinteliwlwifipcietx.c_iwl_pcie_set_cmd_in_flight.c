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
struct iwl_trans_pcie {int ref_cmd_in_flight; int cmd_hold_nic_awake; int /*<<< orphan*/  reg_lock; } ;
struct iwl_trans {struct iwl_cfg* cfg; } ;
struct iwl_host_cmd {int flags; } ;
struct iwl_cfg {TYPE_2__* csr; TYPE_1__* base_params; } ;
struct TYPE_4__ {int /*<<< orphan*/  flag_mac_access_req; int /*<<< orphan*/  flag_mac_clock_ready; int /*<<< orphan*/  flag_val_mac_access_en; } ;
struct TYPE_3__ {scalar_t__ apmg_wake_up_wa; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int CMD_SEND_IN_IDLE ; 
 int /*<<< orphan*/  CSR_GP_CNTRL ; 
 int CSR_GP_CNTRL_REG_FLAG_GOING_TO_SLEEP ; 
 int EIO ; 
 int /*<<< orphan*/  IWL_DEBUG_RPM (struct iwl_trans*,char*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 int /*<<< orphan*/  __iwl_trans_pcie_clear_bit (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __iwl_trans_pcie_set_bit (struct iwl_trans*,int /*<<< orphan*/ ,int) ; 
 int iwl_poll_bit (struct iwl_trans*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  iwl_trans_ref (struct iwl_trans*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_pcie_set_cmd_in_flight(struct iwl_trans *trans,
				      const struct iwl_host_cmd *cmd)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	const struct iwl_cfg *cfg = trans->cfg;
	int ret;

	lockdep_assert_held(&trans_pcie->reg_lock);

	if (!(cmd->flags & CMD_SEND_IN_IDLE) &&
	    !trans_pcie->ref_cmd_in_flight) {
		trans_pcie->ref_cmd_in_flight = true;
		IWL_DEBUG_RPM(trans, "set ref_cmd_in_flight - ref\n");
		iwl_trans_ref(trans);
	}

	/*
	 * wake up the NIC to make sure that the firmware will see the host
	 * command - we will let the NIC sleep once all the host commands
	 * returned. This needs to be done only on NICs that have
	 * apmg_wake_up_wa set.
	 */
	if (cfg->base_params->apmg_wake_up_wa &&
	    !trans_pcie->cmd_hold_nic_awake) {
		__iwl_trans_pcie_set_bit(trans, CSR_GP_CNTRL,
					 BIT(cfg->csr->flag_mac_access_req));

		ret = iwl_poll_bit(trans, CSR_GP_CNTRL,
				   BIT(cfg->csr->flag_val_mac_access_en),
				   (BIT(cfg->csr->flag_mac_clock_ready) |
				    CSR_GP_CNTRL_REG_FLAG_GOING_TO_SLEEP),
				   15000);
		if (ret < 0) {
			__iwl_trans_pcie_clear_bit(trans, CSR_GP_CNTRL,
					BIT(cfg->csr->flag_mac_access_req));
			IWL_ERR(trans, "Failed to wake NIC for hcmd\n");
			return -EIO;
		}
		trans_pcie->cmd_hold_nic_awake = true;
	}

	return 0;
}