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
struct keystone_pcie {int num_legacy_host_irqs; int num_msi_host_irqs; scalar_t__ error_irq; int /*<<< orphan*/ * msi_host_irqs; int /*<<< orphan*/ * legacy_host_irqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct keystone_pcie*) ; 
 int /*<<< orphan*/  ks_dw_pcie_enable_error_irq (struct keystone_pcie*) ; 
 int /*<<< orphan*/  ks_dw_pcie_enable_legacy_irqs (struct keystone_pcie*) ; 
 int /*<<< orphan*/  ks_pcie_legacy_irq_handler ; 
 int /*<<< orphan*/  ks_pcie_msi_irq_handler ; 

__attribute__((used)) static void ks_pcie_setup_interrupts(struct keystone_pcie *ks_pcie)
{
	int i;

	/* Legacy IRQ */
	for (i = 0; i < ks_pcie->num_legacy_host_irqs; i++) {
		irq_set_chained_handler_and_data(ks_pcie->legacy_host_irqs[i],
						 ks_pcie_legacy_irq_handler,
						 ks_pcie);
	}
	ks_dw_pcie_enable_legacy_irqs(ks_pcie);

	/* MSI IRQ */
	if (IS_ENABLED(CONFIG_PCI_MSI)) {
		for (i = 0; i < ks_pcie->num_msi_host_irqs; i++) {
			irq_set_chained_handler_and_data(ks_pcie->msi_host_irqs[i],
							 ks_pcie_msi_irq_handler,
							 ks_pcie);
		}
	}

	if (ks_pcie->error_irq > 0)
		ks_dw_pcie_enable_error_irq(ks_pcie);
}