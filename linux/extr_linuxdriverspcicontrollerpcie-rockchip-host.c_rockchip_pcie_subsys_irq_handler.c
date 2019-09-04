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
struct rockchip_pcie {struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PCIE_CLIENT_INT_LOCAL ; 
 int PCIE_CLIENT_INT_PHY ; 
 int /*<<< orphan*/  PCIE_CLIENT_INT_STATUS ; 
 int PCIE_CORE_INT_CRFO ; 
 int PCIE_CORE_INT_CRFPE ; 
 int PCIE_CORE_INT_CT ; 
 int PCIE_CORE_INT_FCE ; 
 int PCIE_CORE_INT_MMVC ; 
 int PCIE_CORE_INT_MTR ; 
 int PCIE_CORE_INT_PE ; 
 int PCIE_CORE_INT_PRFO ; 
 int PCIE_CORE_INT_PRFPE ; 
 int PCIE_CORE_INT_RRPE ; 
 int PCIE_CORE_INT_RT ; 
 int PCIE_CORE_INT_RTR ; 
 int /*<<< orphan*/  PCIE_CORE_INT_STATUS ; 
 int PCIE_CORE_INT_UCR ; 
 int PCIE_CORE_INT_UTC ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  rockchip_pcie_clr_bw_int (struct rockchip_pcie*) ; 
 int rockchip_pcie_read (struct rockchip_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rockchip_pcie_update_txcredit_mui (struct rockchip_pcie*) ; 
 int /*<<< orphan*/  rockchip_pcie_write (struct rockchip_pcie*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rockchip_pcie_subsys_irq_handler(int irq, void *arg)
{
	struct rockchip_pcie *rockchip = arg;
	struct device *dev = rockchip->dev;
	u32 reg;
	u32 sub_reg;

	reg = rockchip_pcie_read(rockchip, PCIE_CLIENT_INT_STATUS);
	if (reg & PCIE_CLIENT_INT_LOCAL) {
		dev_dbg(dev, "local interrupt received\n");
		sub_reg = rockchip_pcie_read(rockchip, PCIE_CORE_INT_STATUS);
		if (sub_reg & PCIE_CORE_INT_PRFPE)
			dev_dbg(dev, "parity error detected while reading from the PNP receive FIFO RAM\n");

		if (sub_reg & PCIE_CORE_INT_CRFPE)
			dev_dbg(dev, "parity error detected while reading from the Completion Receive FIFO RAM\n");

		if (sub_reg & PCIE_CORE_INT_RRPE)
			dev_dbg(dev, "parity error detected while reading from replay buffer RAM\n");

		if (sub_reg & PCIE_CORE_INT_PRFO)
			dev_dbg(dev, "overflow occurred in the PNP receive FIFO\n");

		if (sub_reg & PCIE_CORE_INT_CRFO)
			dev_dbg(dev, "overflow occurred in the completion receive FIFO\n");

		if (sub_reg & PCIE_CORE_INT_RT)
			dev_dbg(dev, "replay timer timed out\n");

		if (sub_reg & PCIE_CORE_INT_RTR)
			dev_dbg(dev, "replay timer rolled over after 4 transmissions of the same TLP\n");

		if (sub_reg & PCIE_CORE_INT_PE)
			dev_dbg(dev, "phy error detected on receive side\n");

		if (sub_reg & PCIE_CORE_INT_MTR)
			dev_dbg(dev, "malformed TLP received from the link\n");

		if (sub_reg & PCIE_CORE_INT_UCR)
			dev_dbg(dev, "malformed TLP received from the link\n");

		if (sub_reg & PCIE_CORE_INT_FCE)
			dev_dbg(dev, "an error was observed in the flow control advertisements from the other side\n");

		if (sub_reg & PCIE_CORE_INT_CT)
			dev_dbg(dev, "a request timed out waiting for completion\n");

		if (sub_reg & PCIE_CORE_INT_UTC)
			dev_dbg(dev, "unmapped TC error\n");

		if (sub_reg & PCIE_CORE_INT_MMVC)
			dev_dbg(dev, "MSI mask register changes\n");

		rockchip_pcie_write(rockchip, sub_reg, PCIE_CORE_INT_STATUS);
	} else if (reg & PCIE_CLIENT_INT_PHY) {
		dev_dbg(dev, "phy link changes\n");
		rockchip_pcie_update_txcredit_mui(rockchip);
		rockchip_pcie_clr_bw_int(rockchip);
	}

	rockchip_pcie_write(rockchip, reg & PCIE_CLIENT_INT_LOCAL,
			    PCIE_CLIENT_INT_STATUS);

	return IRQ_HANDLED;
}