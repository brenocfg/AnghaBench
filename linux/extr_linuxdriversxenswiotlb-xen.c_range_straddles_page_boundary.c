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
typedef  unsigned int phys_addr_t ;

/* Variables and functions */
 unsigned int XEN_PAGE_MASK ; 
 unsigned int XEN_PAGE_SIZE ; 
 unsigned long XEN_PFN_DOWN (unsigned int) ; 
 scalar_t__ check_pages_physically_contiguous (unsigned long,unsigned int,size_t) ; 

__attribute__((used)) static inline int range_straddles_page_boundary(phys_addr_t p, size_t size)
{
	unsigned long xen_pfn = XEN_PFN_DOWN(p);
	unsigned int offset = p & ~XEN_PAGE_MASK;

	if (offset + size <= XEN_PAGE_SIZE)
		return 0;
	if (check_pages_physically_contiguous(xen_pfn, offset, size))
		return 0;
	return 1;
}