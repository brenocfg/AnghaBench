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

/* Variables and functions */
 unsigned int XEN_PAGE_SHIFT ; 
 unsigned int XEN_PAGE_SIZE ; 
 unsigned long pfn_to_bfn (unsigned long) ; 

__attribute__((used)) static int check_pages_physically_contiguous(unsigned long xen_pfn,
					     unsigned int offset,
					     size_t length)
{
	unsigned long next_bfn;
	int i;
	int nr_pages;

	next_bfn = pfn_to_bfn(xen_pfn);
	nr_pages = (offset + length + XEN_PAGE_SIZE-1) >> XEN_PAGE_SHIFT;

	for (i = 1; i < nr_pages; i++) {
		if (pfn_to_bfn(++xen_pfn) != ++next_bfn)
			return 0;
	}
	return 1;
}