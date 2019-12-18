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
struct page {int dummy; } ;

/* Variables and functions */
 int dissolve_free_huge_page (struct page*) ; 
 int /*<<< orphan*/  hugepages_supported () ; 
 int minimum_order ; 
 struct page* pfn_to_page (unsigned long) ; 

int dissolve_free_huge_pages(unsigned long start_pfn, unsigned long end_pfn)
{
	unsigned long pfn;
	struct page *page;
	int rc = 0;

	if (!hugepages_supported())
		return rc;

	for (pfn = start_pfn; pfn < end_pfn; pfn += 1 << minimum_order) {
		page = pfn_to_page(pfn);
		rc = dissolve_free_huge_page(page);
		if (rc)
			break;
	}

	return rc;
}