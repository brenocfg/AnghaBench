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
struct advk_pcie {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_CTRL_INT_STATUS_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int PCIE_IRQ_CORE_INT ; 
 int /*<<< orphan*/  advk_pcie_handle_int (struct advk_pcie*) ; 
 int advk_readl (struct advk_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advk_writel (struct advk_pcie*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t advk_pcie_irq_handler(int irq, void *arg)
{
	struct advk_pcie *pcie = arg;
	u32 status;

	status = advk_readl(pcie, HOST_CTRL_INT_STATUS_REG);
	if (!(status & PCIE_IRQ_CORE_INT))
		return IRQ_NONE;

	advk_pcie_handle_int(pcie);

	/* Clear interrupt */
	advk_writel(pcie, PCIE_IRQ_CORE_INT, HOST_CTRL_INT_STATUS_REG);

	return IRQ_HANDLED;
}