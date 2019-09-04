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
struct lbtf_private {int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  cmdpendingq; } ;
struct cmd_ctrl_node {TYPE_1__* cmdbuf; int /*<<< orphan*/  list; scalar_t__ result; } ;
struct TYPE_2__ {int /*<<< orphan*/  command; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBTF_DEB_HOST ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_host (char*,...) ; 
 int /*<<< orphan*/  lbtf_deb_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void lbtf_queue_cmd(struct lbtf_private *priv,
			  struct cmd_ctrl_node *cmdnode)
{
	unsigned long flags;
	lbtf_deb_enter(LBTF_DEB_HOST);

	if (!cmdnode) {
		lbtf_deb_host("QUEUE_CMD: cmdnode is NULL\n");
		goto qcmd_done;
	}

	if (!cmdnode->cmdbuf->size) {
		lbtf_deb_host("DNLD_CMD: cmd size is zero\n");
		goto qcmd_done;
	}

	cmdnode->result = 0;
	spin_lock_irqsave(&priv->driver_lock, flags);
	list_add_tail(&cmdnode->list, &priv->cmdpendingq);
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	lbtf_deb_host("QUEUE_CMD: inserted command 0x%04x into cmdpendingq\n",
		     le16_to_cpu(cmdnode->cmdbuf->command));

qcmd_done:
	lbtf_deb_leave(LBTF_DEB_HOST);
}