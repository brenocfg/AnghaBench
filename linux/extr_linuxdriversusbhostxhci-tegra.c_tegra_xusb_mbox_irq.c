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
typedef  int u32 ;
struct tegra_xusb {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int MBOX_SMI_INTR_FW_HANG ; 
 int /*<<< orphan*/  XUSB_CFG_ARU_SMI_INTR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int fpci_readl (struct tegra_xusb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpci_writel (struct tegra_xusb*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tegra_xusb_mbox_irq(int irq, void *data)
{
	struct tegra_xusb *tegra = data;
	u32 value;

	/* clear mailbox interrupts */
	value = fpci_readl(tegra, XUSB_CFG_ARU_SMI_INTR);
	fpci_writel(tegra, value, XUSB_CFG_ARU_SMI_INTR);

	if (value & MBOX_SMI_INTR_FW_HANG)
		dev_err(tegra->dev, "controller firmware hang\n");

	return IRQ_WAKE_THREAD;
}