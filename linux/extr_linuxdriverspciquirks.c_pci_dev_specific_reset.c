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
typedef  scalar_t__ u16 ;
struct pci_dev_reset_methods {int (* reset ) (struct pci_dev*,int) ;scalar_t__ vendor; scalar_t__ device; } ;
struct pci_dev {scalar_t__ vendor; scalar_t__ device; } ;

/* Variables and functions */
 int ENOTTY ; 
 scalar_t__ PCI_ANY_ID ; 
 struct pci_dev_reset_methods* pci_dev_reset_methods ; 
 int stub1 (struct pci_dev*,int) ; 

int pci_dev_specific_reset(struct pci_dev *dev, int probe)
{
	const struct pci_dev_reset_methods *i;

	for (i = pci_dev_reset_methods; i->reset; i++) {
		if ((i->vendor == dev->vendor ||
		     i->vendor == (u16)PCI_ANY_ID) &&
		    (i->device == dev->device ||
		     i->device == (u16)PCI_ANY_ID))
			return i->reset(dev, probe);
	}

	return -ENOTTY;
}