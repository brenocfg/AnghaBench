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
typedef  int /*<<< orphan*/  u32 ;
struct mwifiex_private {int dummy; } ;
struct cmd_ctrl_node {int wait_q_enabled; int cmd_wait_q_woken; int* condition; int /*<<< orphan*/  skb; int /*<<< orphan*/  cmd_skb; void* data_buf; int /*<<< orphan*/  cmd_oid; struct mwifiex_private* priv; } ;

/* Variables and functions */

__attribute__((used)) static void
mwifiex_init_cmd_node(struct mwifiex_private *priv,
		      struct cmd_ctrl_node *cmd_node,
		      u32 cmd_oid, void *data_buf, bool sync)
{
	cmd_node->priv = priv;
	cmd_node->cmd_oid = cmd_oid;
	if (sync) {
		cmd_node->wait_q_enabled = true;
		cmd_node->cmd_wait_q_woken = false;
		cmd_node->condition = &cmd_node->cmd_wait_q_woken;
	}
	cmd_node->data_buf = data_buf;
	cmd_node->cmd_skb = cmd_node->skb;
}