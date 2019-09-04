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
struct pcie_port {int dummy; } ;
struct histb_pcie {int dummy; } ;
struct dw_pcie {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCIE_APP_LTSSM_ENABLE ; 
 int /*<<< orphan*/  PCIE_DEVICE_TYPE_MASK ; 
 int /*<<< orphan*/  PCIE_SYS_CTRL0 ; 
 int /*<<< orphan*/  PCIE_SYS_CTRL7 ; 
 int /*<<< orphan*/  PCIE_WM_RC ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dw_pcie_link_up (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_setup_rc (struct pcie_port*) ; 
 int dw_pcie_wait_for_link (struct dw_pcie*) ; 
 int /*<<< orphan*/  histb_pcie_readl (struct histb_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  histb_pcie_writel (struct histb_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct histb_pcie* to_histb_pcie (struct dw_pcie*) ; 

__attribute__((used)) static int histb_pcie_establish_link(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct histb_pcie *hipcie = to_histb_pcie(pci);
	u32 regval;

	if (dw_pcie_link_up(pci)) {
		dev_info(pci->dev, "Link already up\n");
		return 0;
	}

	/* PCIe RC work mode */
	regval = histb_pcie_readl(hipcie, PCIE_SYS_CTRL0);
	regval &= ~PCIE_DEVICE_TYPE_MASK;
	regval |= PCIE_WM_RC;
	histb_pcie_writel(hipcie, PCIE_SYS_CTRL0, regval);

	/* setup root complex */
	dw_pcie_setup_rc(pp);

	/* assert LTSSM enable */
	regval = histb_pcie_readl(hipcie, PCIE_SYS_CTRL7);
	regval |= PCIE_APP_LTSSM_ENABLE;
	histb_pcie_writel(hipcie, PCIE_SYS_CTRL7, regval);

	return dw_pcie_wait_for_link(pci);
}