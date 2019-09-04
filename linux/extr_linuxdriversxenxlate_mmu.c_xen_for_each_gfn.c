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
typedef  int /*<<< orphan*/  (* xen_gfn_fn_t ) (int /*<<< orphan*/ ,void*) ;
struct page {int dummy; } ;

/* Variables and functions */
 int XEN_PFN_PER_PAGE ; 
 unsigned long page_to_xen_pfn (struct page*) ; 
 int /*<<< orphan*/  pfn_to_gfn (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_for_each_gfn(struct page **pages, unsigned nr_gfn,
			     xen_gfn_fn_t fn, void *data)
{
	unsigned long xen_pfn = 0;
	struct page *page;
	int i;

	for (i = 0; i < nr_gfn; i++) {
		if ((i % XEN_PFN_PER_PAGE) == 0) {
			page = pages[i / XEN_PFN_PER_PAGE];
			xen_pfn = page_to_xen_pfn(page);
		}
		fn(pfn_to_gfn(xen_pfn++), data);
	}
}