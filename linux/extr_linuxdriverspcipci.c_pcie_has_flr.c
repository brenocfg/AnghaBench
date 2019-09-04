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
struct pci_dev {int dev_flags; } ;

/* Variables and functions */
 int PCI_DEV_FLAGS_NO_FLR_RESET ; 
 int /*<<< orphan*/  PCI_EXP_DEVCAP ; 
 int PCI_EXP_DEVCAP_FLR ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

bool pcie_has_flr(struct pci_dev *dev)
{
	u32 cap;

	if (dev->dev_flags & PCI_DEV_FLAGS_NO_FLR_RESET)
		return false;

	pcie_capability_read_dword(dev, PCI_EXP_DEVCAP, &cap);
	return cap & PCI_EXP_DEVCAP_FLR;
}