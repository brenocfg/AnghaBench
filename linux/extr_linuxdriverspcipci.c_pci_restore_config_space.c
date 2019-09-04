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
struct pci_dev {scalar_t__ hdr_type; } ;

/* Variables and functions */
 scalar_t__ PCI_HEADER_TYPE_BRIDGE ; 
 scalar_t__ PCI_HEADER_TYPE_NORMAL ; 
 int /*<<< orphan*/  pci_restore_config_space_range (struct pci_dev*,int,int,int,int) ; 

__attribute__((used)) static void pci_restore_config_space(struct pci_dev *pdev)
{
	if (pdev->hdr_type == PCI_HEADER_TYPE_NORMAL) {
		pci_restore_config_space_range(pdev, 10, 15, 0, false);
		/* Restore BARs before the command register. */
		pci_restore_config_space_range(pdev, 4, 9, 10, false);
		pci_restore_config_space_range(pdev, 0, 3, 0, false);
	} else if (pdev->hdr_type == PCI_HEADER_TYPE_BRIDGE) {
		pci_restore_config_space_range(pdev, 12, 15, 0, false);

		/*
		 * Force rewriting of prefetch registers to avoid S3 resume
		 * issues on Intel PCI bridges that occur when these
		 * registers are not explicitly written.
		 */
		pci_restore_config_space_range(pdev, 9, 11, 0, true);
		pci_restore_config_space_range(pdev, 0, 8, 0, false);
	} else {
		pci_restore_config_space_range(pdev, 0, 15, 0, false);
	}
}