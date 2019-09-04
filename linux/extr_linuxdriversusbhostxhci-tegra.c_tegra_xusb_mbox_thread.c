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
struct tegra_xusb_mbox_msg {int /*<<< orphan*/  cmd; } ;
struct tegra_xusb {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  MBOX_DEST_SMI ; 
 int /*<<< orphan*/  MBOX_OWNER_NONE ; 
 int /*<<< orphan*/  XUSB_CFG_ARU_MBOX_CMD ; 
 int /*<<< orphan*/  XUSB_CFG_ARU_MBOX_DATA_OUT ; 
 int /*<<< orphan*/  XUSB_CFG_ARU_MBOX_OWNER ; 
 int /*<<< orphan*/  fpci_readl (struct tegra_xusb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpci_writel (struct tegra_xusb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_xusb_mbox_cmd_requires_ack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_xusb_mbox_handle (struct tegra_xusb*,struct tegra_xusb_mbox_msg*) ; 
 int /*<<< orphan*/  tegra_xusb_mbox_unpack (struct tegra_xusb_mbox_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tegra_xusb_mbox_thread(int irq, void *data)
{
	struct tegra_xusb *tegra = data;
	struct tegra_xusb_mbox_msg msg;
	u32 value;

	mutex_lock(&tegra->lock);

	value = fpci_readl(tegra, XUSB_CFG_ARU_MBOX_DATA_OUT);
	tegra_xusb_mbox_unpack(&msg, value);

	value = fpci_readl(tegra, XUSB_CFG_ARU_MBOX_CMD);
	value &= ~MBOX_DEST_SMI;
	fpci_writel(tegra, value, XUSB_CFG_ARU_MBOX_CMD);

	/* clear mailbox owner if no ACK/NAK is required */
	if (!tegra_xusb_mbox_cmd_requires_ack(msg.cmd))
		fpci_writel(tegra, MBOX_OWNER_NONE, XUSB_CFG_ARU_MBOX_OWNER);

	tegra_xusb_mbox_handle(tegra, &msg);

	mutex_unlock(&tegra->lock);
	return IRQ_HANDLED;
}