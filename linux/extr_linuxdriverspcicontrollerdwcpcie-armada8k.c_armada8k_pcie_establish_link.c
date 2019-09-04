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
struct armada8k_pcie {struct dw_pcie* pci; } ;

/* Variables and functions */
 int ARCACHE_DEFAULT_VALUE ; 
 int AWCACHE_DEFAULT_VALUE ; 
 int AX_USER_DOMAIN_MASK ; 
 int AX_USER_DOMAIN_SHIFT ; 
 int DOMAIN_OUTER_SHAREABLE ; 
 int PCIE_APP_LTSSM_EN ; 
 int /*<<< orphan*/  PCIE_ARCACHE_TRC_REG ; 
 int /*<<< orphan*/  PCIE_ARUSER_REG ; 
 int /*<<< orphan*/  PCIE_AWCACHE_TRC_REG ; 
 int /*<<< orphan*/  PCIE_AWUSER_REG ; 
 int PCIE_DEVICE_TYPE_MASK ; 
 int PCIE_DEVICE_TYPE_RC ; 
 int PCIE_DEVICE_TYPE_SHIFT ; 
 int /*<<< orphan*/  PCIE_GLOBAL_CONTROL_REG ; 
 int /*<<< orphan*/  PCIE_GLOBAL_INT_MASK1_REG ; 
 int PCIE_INT_A_ASSERT_MASK ; 
 int PCIE_INT_B_ASSERT_MASK ; 
 int PCIE_INT_C_ASSERT_MASK ; 
 int PCIE_INT_D_ASSERT_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dw_pcie_link_up (struct dw_pcie*) ; 
 int dw_pcie_readl_dbi (struct dw_pcie*,int /*<<< orphan*/ ) ; 
 scalar_t__ dw_pcie_wait_for_link (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_writel_dbi (struct dw_pcie*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void armada8k_pcie_establish_link(struct armada8k_pcie *pcie)
{
	struct dw_pcie *pci = pcie->pci;
	u32 reg;

	if (!dw_pcie_link_up(pci)) {
		/* Disable LTSSM state machine to enable configuration */
		reg = dw_pcie_readl_dbi(pci, PCIE_GLOBAL_CONTROL_REG);
		reg &= ~(PCIE_APP_LTSSM_EN);
		dw_pcie_writel_dbi(pci, PCIE_GLOBAL_CONTROL_REG, reg);
	}

	/* Set the device to root complex mode */
	reg = dw_pcie_readl_dbi(pci, PCIE_GLOBAL_CONTROL_REG);
	reg &= ~(PCIE_DEVICE_TYPE_MASK << PCIE_DEVICE_TYPE_SHIFT);
	reg |= PCIE_DEVICE_TYPE_RC << PCIE_DEVICE_TYPE_SHIFT;
	dw_pcie_writel_dbi(pci, PCIE_GLOBAL_CONTROL_REG, reg);

	/* Set the PCIe master AxCache attributes */
	dw_pcie_writel_dbi(pci, PCIE_ARCACHE_TRC_REG, ARCACHE_DEFAULT_VALUE);
	dw_pcie_writel_dbi(pci, PCIE_AWCACHE_TRC_REG, AWCACHE_DEFAULT_VALUE);

	/* Set the PCIe master AxDomain attributes */
	reg = dw_pcie_readl_dbi(pci, PCIE_ARUSER_REG);
	reg &= ~(AX_USER_DOMAIN_MASK << AX_USER_DOMAIN_SHIFT);
	reg |= DOMAIN_OUTER_SHAREABLE << AX_USER_DOMAIN_SHIFT;
	dw_pcie_writel_dbi(pci, PCIE_ARUSER_REG, reg);

	reg = dw_pcie_readl_dbi(pci, PCIE_AWUSER_REG);
	reg &= ~(AX_USER_DOMAIN_MASK << AX_USER_DOMAIN_SHIFT);
	reg |= DOMAIN_OUTER_SHAREABLE << AX_USER_DOMAIN_SHIFT;
	dw_pcie_writel_dbi(pci, PCIE_AWUSER_REG, reg);

	/* Enable INT A-D interrupts */
	reg = dw_pcie_readl_dbi(pci, PCIE_GLOBAL_INT_MASK1_REG);
	reg |= PCIE_INT_A_ASSERT_MASK | PCIE_INT_B_ASSERT_MASK |
	       PCIE_INT_C_ASSERT_MASK | PCIE_INT_D_ASSERT_MASK;
	dw_pcie_writel_dbi(pci, PCIE_GLOBAL_INT_MASK1_REG, reg);

	if (!dw_pcie_link_up(pci)) {
		/* Configuration done. Start LTSSM */
		reg = dw_pcie_readl_dbi(pci, PCIE_GLOBAL_CONTROL_REG);
		reg |= PCIE_APP_LTSSM_EN;
		dw_pcie_writel_dbi(pci, PCIE_GLOBAL_CONTROL_REG, reg);
	}

	/* Wait until the link becomes active again */
	if (dw_pcie_wait_for_link(pci))
		dev_err(pci->dev, "Link not up after reconfiguration\n");
}