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
struct lbs_private {int /*<<< orphan*/  waitq; int /*<<< orphan*/ * cur_cmd; } ;
struct cmd_ctrl_node {int result; int cmdwaitqwoken; scalar_t__ callback; int /*<<< orphan*/  cmdwait_q; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lbs_cleanup_and_insert_cmd (struct lbs_private*,struct cmd_ctrl_node*) ; 
 scalar_t__ lbs_cmd_async_callback ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void __lbs_complete_command(struct lbs_private *priv, struct cmd_ctrl_node *cmd,
			    int result)
{
	/*
	 * Normally, commands are removed from cmdpendingq before being
	 * submitted. However, we can arrive here on alternative codepaths
	 * where the command is still pending. Make sure the command really
	 * isn't part of a list at this point.
	 */
	list_del_init(&cmd->list);

	cmd->result = result;
	cmd->cmdwaitqwoken = 1;
	wake_up(&cmd->cmdwait_q);

	if (!cmd->callback || cmd->callback == lbs_cmd_async_callback)
		__lbs_cleanup_and_insert_cmd(priv, cmd);
	priv->cur_cmd = NULL;
	wake_up(&priv->waitq);
}