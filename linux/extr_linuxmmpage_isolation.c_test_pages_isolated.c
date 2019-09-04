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
struct zone {int /*<<< orphan*/  lock; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 struct page* __first_valid_page (unsigned long,unsigned long) ; 
 unsigned long __test_page_isolated_in_pageblock (unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  is_migrate_isolate_page (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 unsigned long pageblock_nr_pages ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_test_pages_isolated (unsigned long,unsigned long,unsigned long) ; 

int test_pages_isolated(unsigned long start_pfn, unsigned long end_pfn,
			bool skip_hwpoisoned_pages)
{
	unsigned long pfn, flags;
	struct page *page;
	struct zone *zone;

	/*
	 * Note: pageblock_nr_pages != MAX_ORDER. Then, chunks of free pages
	 * are not aligned to pageblock_nr_pages.
	 * Then we just check migratetype first.
	 */
	for (pfn = start_pfn; pfn < end_pfn; pfn += pageblock_nr_pages) {
		page = __first_valid_page(pfn, pageblock_nr_pages);
		if (page && !is_migrate_isolate_page(page))
			break;
	}
	page = __first_valid_page(start_pfn, end_pfn - start_pfn);
	if ((pfn < end_pfn) || !page)
		return -EBUSY;
	/* Check all pages are free or marked as ISOLATED */
	zone = page_zone(page);
	spin_lock_irqsave(&zone->lock, flags);
	pfn = __test_page_isolated_in_pageblock(start_pfn, end_pfn,
						skip_hwpoisoned_pages);
	spin_unlock_irqrestore(&zone->lock, flags);

	trace_test_pages_isolated(start_pfn, end_pfn, pfn);

	return pfn < end_pfn ? -EBUSY : 0;
}