#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pci_driver {int dummy; } ;
struct pci_dev {TYPE_1__* resource; struct pci_driver* driver; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IORESOURCE_BUSY ; 
 int PCI_ROM_RESOURCE ; 
 struct pci_driver pci_compat_driver ; 

struct pci_driver *pci_dev_driver(const struct pci_dev *dev)
{
	if (dev->driver)
		return dev->driver;
	else {
		int i;
		for (i = 0; i <= PCI_ROM_RESOURCE; i++)
			if (dev->resource[i].flags & IORESOURCE_BUSY)
				return &pci_compat_driver;
	}
	return NULL;
}