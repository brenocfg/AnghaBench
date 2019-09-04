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
struct spear13xx_pcie {struct pcie_app_reg* app_base; struct dw_pcie* pci; } ;
struct pcie_port {int dummy; } ;
struct pcie_app_reg {int /*<<< orphan*/  int_mask; } ;
struct dw_pcie {struct pcie_port pp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int MSI_CTRL_INT ; 
 int /*<<< orphan*/  dw_pcie_msi_init (struct pcie_port*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spear13xx_pcie_enable_interrupts(struct spear13xx_pcie *spear13xx_pcie)
{
	struct dw_pcie *pci = spear13xx_pcie->pci;
	struct pcie_port *pp = &pci->pp;
	struct pcie_app_reg *app_reg = spear13xx_pcie->app_base;

	/* Enable MSI interrupt */
	if (IS_ENABLED(CONFIG_PCI_MSI)) {
		dw_pcie_msi_init(pp);
		writel(readl(&app_reg->int_mask) |
				MSI_CTRL_INT, &app_reg->int_mask);
	}
}