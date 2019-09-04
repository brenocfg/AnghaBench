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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PCI_EXP_AER_FLAGS ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 scalar_t__ pcie_aer_get_firmware_first (struct pci_dev*) ; 
 int pcie_capability_clear_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int pci_disable_pcie_error_reporting(struct pci_dev *dev)
{
	if (pcie_aer_get_firmware_first(dev))
		return -EIO;

	return pcie_capability_clear_word(dev, PCI_EXP_DEVCTL,
					  PCI_EXP_AER_FLAGS);
}