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
typedef  int u32 ;
struct keystone_pcie {TYPE_1__* pci; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ERR_FATAL_IRQ ; 
 int ERR_IRQ_ALL ; 
 int /*<<< orphan*/  ERR_IRQ_STATUS ; 
 int /*<<< orphan*/  ERR_IRQ_STATUS_RAW ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int ks_dw_app_readl (struct keystone_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_dw_app_writel (struct keystone_pcie*,int /*<<< orphan*/ ,int) ; 

irqreturn_t ks_dw_pcie_handle_error_irq(struct keystone_pcie *ks_pcie)
{
	u32 status;

	status = ks_dw_app_readl(ks_pcie, ERR_IRQ_STATUS_RAW) & ERR_IRQ_ALL;
	if (!status)
		return IRQ_NONE;

	if (status & ERR_FATAL_IRQ)
		dev_err(ks_pcie->pci->dev, "fatal error (status %#010x)\n",
			status);

	/* Ack the IRQ; status bits are RW1C */
	ks_dw_app_writel(ks_pcie, ERR_IRQ_STATUS, status);
	return IRQ_HANDLED;
}