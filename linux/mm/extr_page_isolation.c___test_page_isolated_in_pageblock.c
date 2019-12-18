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
 scalar_t__ PageBuddy (struct page*) ; 
 scalar_t__ PageHWPoison (struct page*) ; 
 int page_order (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid_within (unsigned long) ; 

__attribute__((used)) static unsigned long
__test_page_isolated_in_pageblock(unsigned long pfn, unsigned long end_pfn,
				  bool skip_hwpoisoned_pages)
{
	struct page *page;

	while (pfn < end_pfn) {
		if (!pfn_valid_within(pfn)) {
			pfn++;
			continue;
		}
		page = pfn_to_page(pfn);
		if (PageBuddy(page))
			/*
			 * If the page is on a free list, it has to be on
			 * the correct MIGRATE_ISOLATE freelist. There is no
			 * simple way to verify that as VM_BUG_ON(), though.
			 */
			pfn += 1 << page_order(page);
		else if (skip_hwpoisoned_pages && PageHWPoison(page))
			/* A HWPoisoned page cannot be also PageBuddy */
			pfn++;
		else
			break;
	}

	return pfn;
}