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
struct pcie_port {int dummy; } ;
struct dw_pcie {struct pcie_port pp; } ;
struct artpec6_pcie {struct dw_pcie* pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_pcie_msi_init (struct pcie_port*) ; 

__attribute__((used)) static void artpec6_pcie_enable_interrupts(struct artpec6_pcie *artpec6_pcie)
{
	struct dw_pcie *pci = artpec6_pcie->pci;
	struct pcie_port *pp = &pci->pp;

	if (IS_ENABLED(CONFIG_PCI_MSI))
		dw_pcie_msi_init(pp);
}