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
typedef  int u16 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_LNKCTL ; 
 int PCI_EXP_LNKCTL_RCB ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 struct pci_dev* pcie_find_root_port (struct pci_dev*) ; 

__attribute__((used)) static bool pcie_root_rcb_set(struct pci_dev *dev)
{
	struct pci_dev *rp = pcie_find_root_port(dev);
	u16 lnkctl;

	if (!rp)
		return false;

	pcie_capability_read_word(rp, PCI_EXP_LNKCTL, &lnkctl);
	if (lnkctl & PCI_EXP_LNKCTL_RCB)
		return true;

	return false;
}