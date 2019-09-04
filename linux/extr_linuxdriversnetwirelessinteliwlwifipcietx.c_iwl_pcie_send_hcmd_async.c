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
struct iwl_trans {int dummy; } ;
struct iwl_host_cmd {int flags; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int CMD_WANT_SKB ; 
 int EINVAL ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iwl_get_cmd_string (struct iwl_trans*,int /*<<< orphan*/ ) ; 
 int iwl_pcie_enqueue_hcmd (struct iwl_trans*,struct iwl_host_cmd*) ; 

__attribute__((used)) static int iwl_pcie_send_hcmd_async(struct iwl_trans *trans,
				    struct iwl_host_cmd *cmd)
{
	int ret;

	/* An asynchronous command can not expect an SKB to be set. */
	if (WARN_ON(cmd->flags & CMD_WANT_SKB))
		return -EINVAL;

	ret = iwl_pcie_enqueue_hcmd(trans, cmd);
	if (ret < 0) {
		IWL_ERR(trans,
			"Error sending %s: enqueue_hcmd failed: %d\n",
			iwl_get_cmd_string(trans, cmd->id), ret);
		return ret;
	}
	return 0;
}