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
struct pci_dev {int reset_fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_aer_init (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_allocate_cap_save_buffers (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_ats_init (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_configure_ari (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_ea_init (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_acs (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iov_init (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_msi_setup_pci_dev (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_pm_init (struct pci_dev*) ; 
 scalar_t__ pci_probe_reset_function (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_ptm_init (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_vpd_init (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_report_downtraining (struct pci_dev*) ; 

__attribute__((used)) static void pci_init_capabilities(struct pci_dev *dev)
{
	/* Enhanced Allocation */
	pci_ea_init(dev);

	/* Setup MSI caps & disable MSI/MSI-X interrupts */
	pci_msi_setup_pci_dev(dev);

	/* Buffers for saving PCIe and PCI-X capabilities */
	pci_allocate_cap_save_buffers(dev);

	/* Power Management */
	pci_pm_init(dev);

	/* Vital Product Data */
	pci_vpd_init(dev);

	/* Alternative Routing-ID Forwarding */
	pci_configure_ari(dev);

	/* Single Root I/O Virtualization */
	pci_iov_init(dev);

	/* Address Translation Services */
	pci_ats_init(dev);

	/* Enable ACS P2P upstream forwarding */
	pci_enable_acs(dev);

	/* Precision Time Measurement */
	pci_ptm_init(dev);

	/* Advanced Error Reporting */
	pci_aer_init(dev);

	pcie_report_downtraining(dev);

	if (pci_probe_reset_function(dev) == 0)
		dev->reset_fn = 1;
}