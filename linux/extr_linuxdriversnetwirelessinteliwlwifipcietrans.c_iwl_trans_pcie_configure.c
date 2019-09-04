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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {scalar_t__ reg_state; } ;
struct iwl_trans_pcie {scalar_t__ n_no_reclaim_cmds; int page_offs; int dev_cmd_offs; TYPE_1__ napi_dev; int /*<<< orphan*/  sw_csum_tx; int /*<<< orphan*/  scd_set_active; int /*<<< orphan*/  bc_table_dword; int /*<<< orphan*/  rx_buf_size; int /*<<< orphan*/  rx_page_order; int /*<<< orphan*/  no_reclaim_cmds; int /*<<< orphan*/  cmd_q_wdg_timeout; int /*<<< orphan*/  cmd_fifo; int /*<<< orphan*/  cmd_queue; } ;
struct iwl_trans_config {scalar_t__ n_no_reclaim_cmds; int cb_data_offs; int /*<<< orphan*/  command_groups_size; int /*<<< orphan*/  command_groups; int /*<<< orphan*/  sw_csum_tx; int /*<<< orphan*/  scd_set_active; int /*<<< orphan*/  bc_table_dword; int /*<<< orphan*/  rx_buf_size; int /*<<< orphan*/  no_reclaim_cmds; int /*<<< orphan*/  cmd_q_wdg_timeout; int /*<<< orphan*/  cmd_fifo; int /*<<< orphan*/  cmd_queue; } ;
struct iwl_trans {int /*<<< orphan*/  command_groups_size; int /*<<< orphan*/  command_groups; } ;

/* Variables and functions */
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 scalar_t__ MAX_NO_RECLAIM_CMDS ; 
 scalar_t__ NETREG_DUMMY ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  init_dummy_netdev (TYPE_1__*) ; 
 int /*<<< orphan*/  iwl_trans_get_rb_size_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void iwl_trans_pcie_configure(struct iwl_trans *trans,
				     const struct iwl_trans_config *trans_cfg)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);

	trans_pcie->cmd_queue = trans_cfg->cmd_queue;
	trans_pcie->cmd_fifo = trans_cfg->cmd_fifo;
	trans_pcie->cmd_q_wdg_timeout = trans_cfg->cmd_q_wdg_timeout;
	if (WARN_ON(trans_cfg->n_no_reclaim_cmds > MAX_NO_RECLAIM_CMDS))
		trans_pcie->n_no_reclaim_cmds = 0;
	else
		trans_pcie->n_no_reclaim_cmds = trans_cfg->n_no_reclaim_cmds;
	if (trans_pcie->n_no_reclaim_cmds)
		memcpy(trans_pcie->no_reclaim_cmds, trans_cfg->no_reclaim_cmds,
		       trans_pcie->n_no_reclaim_cmds * sizeof(u8));

	trans_pcie->rx_buf_size = trans_cfg->rx_buf_size;
	trans_pcie->rx_page_order =
		iwl_trans_get_rb_size_order(trans_pcie->rx_buf_size);

	trans_pcie->bc_table_dword = trans_cfg->bc_table_dword;
	trans_pcie->scd_set_active = trans_cfg->scd_set_active;
	trans_pcie->sw_csum_tx = trans_cfg->sw_csum_tx;

	trans_pcie->page_offs = trans_cfg->cb_data_offs;
	trans_pcie->dev_cmd_offs = trans_cfg->cb_data_offs + sizeof(void *);

	trans->command_groups = trans_cfg->command_groups;
	trans->command_groups_size = trans_cfg->command_groups_size;

	/* Initialize NAPI here - it should be before registering to mac80211
	 * in the opmode but after the HW struct is allocated.
	 * As this function may be called again in some corner cases don't
	 * do anything if NAPI was already initialized.
	 */
	if (trans_pcie->napi_dev.reg_state != NETREG_DUMMY)
		init_dummy_netdev(&trans_pcie->napi_dev);
}