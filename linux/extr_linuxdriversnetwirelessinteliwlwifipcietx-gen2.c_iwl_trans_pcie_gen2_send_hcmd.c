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
struct iwl_trans {int /*<<< orphan*/  status; } ;
struct iwl_host_cmd {int flags; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int CMD_ASYNC ; 
 int CMD_SEND_IN_RFKILL ; 
 int CMD_WANT_SKB ; 
 int EINVAL ; 
 int ERFKILL ; 
 int /*<<< orphan*/  IWL_DEBUG_RF_KILL (struct iwl_trans*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  STATUS_RFKILL_OPMODE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iwl_get_cmd_string (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int iwl_pcie_gen2_enqueue_hcmd (struct iwl_trans*,struct iwl_host_cmd*) ; 
 int iwl_pcie_gen2_send_hcmd_sync (struct iwl_trans*,struct iwl_host_cmd*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int iwl_trans_pcie_gen2_send_hcmd(struct iwl_trans *trans,
				  struct iwl_host_cmd *cmd)
{
	if (!(cmd->flags & CMD_SEND_IN_RFKILL) &&
	    test_bit(STATUS_RFKILL_OPMODE, &trans->status)) {
		IWL_DEBUG_RF_KILL(trans, "Dropping CMD 0x%x: RF KILL\n",
				  cmd->id);
		return -ERFKILL;
	}

	if (cmd->flags & CMD_ASYNC) {
		int ret;

		/* An asynchronous command can not expect an SKB to be set. */
		if (WARN_ON(cmd->flags & CMD_WANT_SKB))
			return -EINVAL;

		ret = iwl_pcie_gen2_enqueue_hcmd(trans, cmd);
		if (ret < 0) {
			IWL_ERR(trans,
				"Error sending %s: enqueue_hcmd failed: %d\n",
				iwl_get_cmd_string(trans, cmd->id), ret);
			return ret;
		}
		return 0;
	}

	return iwl_pcie_gen2_send_hcmd_sync(trans, cmd);
}