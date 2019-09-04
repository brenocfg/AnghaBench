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
struct lbs_private {scalar_t__ psstate; int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  cmdpendingq; } ;
struct cmd_ds_802_11_ps_mode {scalar_t__ action; } ;
struct cmd_ctrl_node {TYPE_1__* cmdbuf; int /*<<< orphan*/  list; scalar_t__ result; } ;
struct TYPE_2__ {int /*<<< orphan*/  command; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 scalar_t__ CMD_802_11_PS_MODE ; 
 scalar_t__ CMD_802_11_WAKEUP_CONFIRM ; 
 int /*<<< orphan*/  PS_MODE_ACTION_EXIT_PS ; 
 scalar_t__ PS_STATE_FULL_POWER ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_host (char*,...) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void lbs_queue_cmd(struct lbs_private *priv,
			  struct cmd_ctrl_node *cmdnode)
{
	unsigned long flags;
	int addtail = 1;

	if (!cmdnode) {
		lbs_deb_host("QUEUE_CMD: cmdnode is NULL\n");
		return;
	}
	if (!cmdnode->cmdbuf->size) {
		lbs_deb_host("DNLD_CMD: cmd size is zero\n");
		return;
	}
	cmdnode->result = 0;

	/* Exit_PS command needs to be queued in the header always. */
	if (le16_to_cpu(cmdnode->cmdbuf->command) == CMD_802_11_PS_MODE) {
		struct cmd_ds_802_11_ps_mode *psm = (void *)cmdnode->cmdbuf;

		if (psm->action == cpu_to_le16(PS_MODE_ACTION_EXIT_PS)) {
			if (priv->psstate != PS_STATE_FULL_POWER)
				addtail = 0;
		}
	}

	if (le16_to_cpu(cmdnode->cmdbuf->command) == CMD_802_11_WAKEUP_CONFIRM)
		addtail = 0;

	spin_lock_irqsave(&priv->driver_lock, flags);

	if (addtail)
		list_add_tail(&cmdnode->list, &priv->cmdpendingq);
	else
		list_add(&cmdnode->list, &priv->cmdpendingq);

	spin_unlock_irqrestore(&priv->driver_lock, flags);

	lbs_deb_host("QUEUE_CMD: inserted command 0x%04x into cmdpendingq\n",
		     le16_to_cpu(cmdnode->cmdbuf->command));
}