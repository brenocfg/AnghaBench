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
struct resource {int end; scalar_t__ start; int /*<<< orphan*/  flags; } ;
struct pci_dev {int revision; struct resource* resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_UNSET ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,unsigned int) ; 
 int pci_resource_len (struct pci_dev*,unsigned int) ; 
 int pci_resource_start (struct pci_dev*,unsigned int) ; 

__attribute__((used)) static void quirk_plx_pci9050(struct pci_dev *dev)
{
	unsigned int bar;

	/* Fixed in revision 2 (PCI 9052). */
	if (dev->revision >= 2)
		return;
	for (bar = 0; bar <= 1; bar++)
		if (pci_resource_len(dev, bar) == 0x80 &&
		    (pci_resource_start(dev, bar) & 0x80)) {
			struct resource *r = &dev->resource[bar];
			pci_info(dev, "Re-allocating PLX PCI 9050 BAR %u to length 256 to avoid bit 7 bug\n",
				 bar);
			r->flags |= IORESOURCE_UNSET;
			r->start = 0;
			r->end = 0xff;
		}
}