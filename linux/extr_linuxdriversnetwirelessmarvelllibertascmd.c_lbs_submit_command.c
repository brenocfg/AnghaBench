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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  u8 ;
struct lbs_private {int (* hw_host_to_card ) (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ;int wakeup_dev_required; int is_deep_sleep; int /*<<< orphan*/  command_timer; scalar_t__ dnld_sent; scalar_t__ is_auto_deep_sleep_enabled; int /*<<< orphan*/  dev; int /*<<< orphan*/  driver_lock; struct cmd_ctrl_node* cur_cmd; int /*<<< orphan*/  seqnum; } ;
struct cmd_header {int /*<<< orphan*/  seqnum; int /*<<< orphan*/  command; int /*<<< orphan*/  size; } ;
struct cmd_ctrl_node {struct cmd_header* cmdbuf; } ;

/* Variables and functions */
 scalar_t__ CMD_802_11_ASSOCIATE ; 
 scalar_t__ CMD_802_11_DEEP_SLEEP ; 
 scalar_t__ CMD_802_11_SCAN ; 
 scalar_t__ DNLD_RES_RECEIVED ; 
 int HZ ; 
 int /*<<< orphan*/  LBS_DEB_CMD ; 
 int /*<<< orphan*/  MVMS_CMD ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lbs_complete_command (struct lbs_private*,struct cmd_ctrl_node*,int) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lbs_deb_hex (int /*<<< orphan*/ ,char*,void*,scalar_t__) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct lbs_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void lbs_submit_command(struct lbs_private *priv,
			       struct cmd_ctrl_node *cmdnode)
{
	unsigned long flags;
	struct cmd_header *cmd;
	uint16_t cmdsize;
	uint16_t command;
	int timeo = 3 * HZ;
	int ret;

	cmd = cmdnode->cmdbuf;

	spin_lock_irqsave(&priv->driver_lock, flags);
	priv->seqnum++;
	cmd->seqnum = cpu_to_le16(priv->seqnum);
	priv->cur_cmd = cmdnode;
	spin_unlock_irqrestore(&priv->driver_lock, flags);

	cmdsize = le16_to_cpu(cmd->size);
	command = le16_to_cpu(cmd->command);

	/* These commands take longer */
	if (command == CMD_802_11_SCAN || command == CMD_802_11_ASSOCIATE)
		timeo = 5 * HZ;

	lbs_deb_cmd("DNLD_CMD: command 0x%04x, seq %d, size %d\n",
		     command, le16_to_cpu(cmd->seqnum), cmdsize);
	lbs_deb_hex(LBS_DEB_CMD, "DNLD_CMD", (void *) cmdnode->cmdbuf, cmdsize);

	ret = priv->hw_host_to_card(priv, MVMS_CMD, (u8 *) cmd, cmdsize);

	if (ret) {
		netdev_info(priv->dev, "DNLD_CMD: hw_host_to_card failed: %d\n",
			    ret);
		/* Reset dnld state machine, report failure */
		priv->dnld_sent = DNLD_RES_RECEIVED;
		lbs_complete_command(priv, cmdnode, ret);
	}

	if (command == CMD_802_11_DEEP_SLEEP) {
		if (priv->is_auto_deep_sleep_enabled) {
			priv->wakeup_dev_required = 1;
			priv->dnld_sent = 0;
		}
		priv->is_deep_sleep = 1;
		lbs_complete_command(priv, cmdnode, 0);
	} else {
		/* Setup the timer after transmit command */
		mod_timer(&priv->command_timer, jiffies + timeo);
	}
}