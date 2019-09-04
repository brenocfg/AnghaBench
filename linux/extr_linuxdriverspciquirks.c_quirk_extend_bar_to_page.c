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
struct resource {int flags; scalar_t__ start; scalar_t__ end; } ;
struct pci_dev {struct resource* resource; } ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 int IORESOURCE_UNSET ; 
 scalar_t__ PAGE_SIZE ; 
 int PCI_STD_RESOURCE_END ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int,struct resource*) ; 
 scalar_t__ resource_size (struct resource*) ; 

__attribute__((used)) static void quirk_extend_bar_to_page(struct pci_dev *dev)
{
	int i;

	for (i = 0; i <= PCI_STD_RESOURCE_END; i++) {
		struct resource *r = &dev->resource[i];

		if (r->flags & IORESOURCE_MEM && resource_size(r) < PAGE_SIZE) {
			r->end = PAGE_SIZE - 1;
			r->start = 0;
			r->flags |= IORESOURCE_UNSET;
			pci_info(dev, "expanded BAR %d to page size: %pR\n",
				 i, r);
		}
	}
}