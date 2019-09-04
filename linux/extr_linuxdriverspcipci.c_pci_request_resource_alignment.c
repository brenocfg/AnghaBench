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
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 int IORESOURCE_PCI_FIXED ; 
 int IORESOURCE_SIZEALIGN ; 
 int IORESOURCE_STARTALIGN ; 
 int IORESOURCE_UNSET ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int,struct resource*,unsigned long long) ; 
 scalar_t__ resource_size (struct resource*) ; 

__attribute__((used)) static void pci_request_resource_alignment(struct pci_dev *dev, int bar,
					   resource_size_t align, bool resize)
{
	struct resource *r = &dev->resource[bar];
	resource_size_t size;

	if (!(r->flags & IORESOURCE_MEM))
		return;

	if (r->flags & IORESOURCE_PCI_FIXED) {
		pci_info(dev, "BAR%d %pR: ignoring requested alignment %#llx\n",
			 bar, r, (unsigned long long)align);
		return;
	}

	size = resource_size(r);
	if (size >= align)
		return;

	/*
	 * Increase the alignment of the resource.  There are two ways we
	 * can do this:
	 *
	 * 1) Increase the size of the resource.  BARs are aligned on their
	 *    size, so when we reallocate space for this resource, we'll
	 *    allocate it with the larger alignment.  This also prevents
	 *    assignment of any other BARs inside the alignment region, so
	 *    if we're requesting page alignment, this means no other BARs
	 *    will share the page.
	 *
	 *    The disadvantage is that this makes the resource larger than
	 *    the hardware BAR, which may break drivers that compute things
	 *    based on the resource size, e.g., to find registers at a
	 *    fixed offset before the end of the BAR.
	 *
	 * 2) Retain the resource size, but use IORESOURCE_STARTALIGN and
	 *    set r->start to the desired alignment.  By itself this
	 *    doesn't prevent other BARs being put inside the alignment
	 *    region, but if we realign *every* resource of every device in
	 *    the system, none of them will share an alignment region.
	 *
	 * When the user has requested alignment for only some devices via
	 * the "pci=resource_alignment" argument, "resize" is true and we
	 * use the first method.  Otherwise we assume we're aligning all
	 * devices and we use the second.
	 */

	pci_info(dev, "BAR%d %pR: requesting alignment to %#llx\n",
		 bar, r, (unsigned long long)align);

	if (resize) {
		r->start = 0;
		r->end = align - 1;
	} else {
		r->flags &= ~IORESOURCE_SIZEALIGN;
		r->flags |= IORESOURCE_STARTALIGN;
		r->start = align;
		r->end = r->start + size - 1;
	}
	r->flags |= IORESOURCE_UNSET;
}