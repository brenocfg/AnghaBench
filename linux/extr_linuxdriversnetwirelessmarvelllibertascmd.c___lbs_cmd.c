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
typedef  int /*<<< orphan*/  uint16_t ;
struct lbs_private {int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  dev; } ;
struct cmd_header {int dummy; } ;
struct cmd_ctrl_node {int result; int /*<<< orphan*/  cmdwaitqwoken; int /*<<< orphan*/  cmdwait_q; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct cmd_ctrl_node*) ; 
 int PTR_ERR (struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  __lbs_cleanup_and_insert_cmd (struct lbs_private*,struct cmd_ctrl_node*) ; 
 struct cmd_ctrl_node* __lbs_cmd_async (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_header*,int,int (*) (struct lbs_private*,unsigned long,struct cmd_header*),unsigned long) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __lbs_cmd(struct lbs_private *priv, uint16_t command,
	      struct cmd_header *in_cmd, int in_cmd_size,
	      int (*callback)(struct lbs_private *, unsigned long, struct cmd_header *),
	      unsigned long callback_arg)
{
	struct cmd_ctrl_node *cmdnode;
	unsigned long flags;
	int ret = 0;

	cmdnode = __lbs_cmd_async(priv, command, in_cmd, in_cmd_size,
				  callback, callback_arg);
	if (IS_ERR(cmdnode)) {
		ret = PTR_ERR(cmdnode);
		goto done;
	}

	might_sleep();

	/*
	 * Be careful with signals here. A signal may be received as the system
	 * goes into suspend or resume. We do not want this to interrupt the
	 * command, so we perform an uninterruptible sleep.
	 */
	wait_event(cmdnode->cmdwait_q, cmdnode->cmdwaitqwoken);

	spin_lock_irqsave(&priv->driver_lock, flags);
	ret = cmdnode->result;
	if (ret)
		netdev_info(priv->dev, "PREP_CMD: command 0x%04x failed: %d\n",
			    command, ret);

	__lbs_cleanup_and_insert_cmd(priv, cmdnode);
	spin_unlock_irqrestore(&priv->driver_lock, flags);

done:
	return ret;
}