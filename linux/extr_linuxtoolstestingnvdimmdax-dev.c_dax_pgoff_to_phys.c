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
struct resource {unsigned long start; unsigned long end; } ;
struct page {int dummy; } ;
struct dev_dax {int num_resources; TYPE_1__* region; struct resource* res; } ;
typedef  unsigned long phys_addr_t ;
typedef  int pgoff_t ;
struct TYPE_2__ {int align; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 unsigned long PFN_PHYS (int /*<<< orphan*/ ) ; 
 scalar_t__ PHYS_PFN (int /*<<< orphan*/ ) ; 
 scalar_t__ get_nfit_res (unsigned long) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct page* vmalloc_to_page (void*) ; 

phys_addr_t dax_pgoff_to_phys(struct dev_dax *dev_dax, pgoff_t pgoff,
		unsigned long size)
{
	struct resource *res;
	phys_addr_t addr;
	int i;

	for (i = 0; i < dev_dax->num_resources; i++) {
		res = &dev_dax->res[i];
		addr = pgoff * PAGE_SIZE + res->start;
		if (addr >= res->start && addr <= res->end)
			break;
		pgoff -= PHYS_PFN(resource_size(res));
	}

	if (i < dev_dax->num_resources) {
		res = &dev_dax->res[i];
		if (addr + size - 1 <= res->end) {
			if (get_nfit_res(addr)) {
				struct page *page;

				if (dev_dax->region->align > PAGE_SIZE)
					return -1;

				page = vmalloc_to_page((void *)addr);
				return PFN_PHYS(page_to_pfn(page));
			} else
				return addr;
		}
	}

	return -1;
}