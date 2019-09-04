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
struct dw_pcie {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PCIE_GLB_STS_PHY_LINK_UP ; 
 int PCIE_GLB_STS_RDLH_LINK_UP ; 
 int /*<<< orphan*/  PCIE_GLOBAL_STATUS_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int dw_pcie_readl_dbi (struct dw_pcie*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armada8k_pcie_link_up(struct dw_pcie *pci)
{
	u32 reg;
	u32 mask = PCIE_GLB_STS_RDLH_LINK_UP | PCIE_GLB_STS_PHY_LINK_UP;

	reg = dw_pcie_readl_dbi(pci, PCIE_GLOBAL_STATUS_REG);

	if ((reg & mask) == mask)
		return 1;

	dev_dbg(pci->dev, "No link detected (Global-Status: 0x%08x).\n", reg);
	return 0;
}