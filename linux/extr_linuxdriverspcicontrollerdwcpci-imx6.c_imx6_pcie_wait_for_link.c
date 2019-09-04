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
struct imx6_pcie {struct dw_pcie* pci; } ;
struct dw_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PCIE_PHY_DEBUG_R0 ; 
 int /*<<< orphan*/  PCIE_PHY_DEBUG_R1 ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_pcie_readl_dbi (struct dw_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_pcie_wait_for_link (struct dw_pcie*) ; 

__attribute__((used)) static int imx6_pcie_wait_for_link(struct imx6_pcie *imx6_pcie)
{
	struct dw_pcie *pci = imx6_pcie->pci;
	struct device *dev = pci->dev;

	/* check if the link is up or not */
	if (!dw_pcie_wait_for_link(pci))
		return 0;

	dev_dbg(dev, "DEBUG_R0: 0x%08x, DEBUG_R1: 0x%08x\n",
		dw_pcie_readl_dbi(pci, PCIE_PHY_DEBUG_R0),
		dw_pcie_readl_dbi(pci, PCIE_PHY_DEBUG_R1));
	return -ETIMEDOUT;
}