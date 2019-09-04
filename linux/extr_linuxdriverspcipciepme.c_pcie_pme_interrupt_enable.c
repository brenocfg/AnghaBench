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
 int /*<<< orphan*/  PCI_EXP_RTCTL ; 
 int /*<<< orphan*/  PCI_EXP_RTCTL_PMEIE ; 
 int /*<<< orphan*/  pcie_capability_clear_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_capability_set_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pcie_pme_interrupt_enable(struct pci_dev *dev, bool enable)
{
	if (enable)
		pcie_capability_set_word(dev, PCI_EXP_RTCTL,
					 PCI_EXP_RTCTL_PMEIE);
	else
		pcie_capability_clear_word(dev, PCI_EXP_RTCTL,
					   PCI_EXP_RTCTL_PMEIE);
}