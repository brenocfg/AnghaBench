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
struct resource {int dummy; } ;

/* Variables and functions */

void pci_unmap_iospace(struct resource *res)
{
#if defined(PCI_IOBASE) && defined(CONFIG_MMU)
	unsigned long vaddr = (unsigned long)PCI_IOBASE + res->start;

	unmap_kernel_range(vaddr, resource_size(res));
#endif
}