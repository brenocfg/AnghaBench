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
struct zone {TYPE_1__* free_area; } ;
struct page {int /*<<< orphan*/  lru; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_CMA ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MIGRATE_MOVABLE ; 
 int /*<<< orphan*/  PageBuddy (struct page*) ; 
 int /*<<< orphan*/  __mod_zone_freepage_state (struct zone*,unsigned long,int) ; 
 int get_pageblock_migratetype (struct page*) ; 
 int /*<<< orphan*/  is_migrate_cma (int) ; 
 int /*<<< orphan*/  is_migrate_highatomic (int) ; 
 int /*<<< orphan*/  is_migrate_isolate (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 unsigned long min_wmark_pages (struct zone*) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  pageblock_nr_pages ; 
 int pageblock_order ; 
 int /*<<< orphan*/  rmv_page_order (struct page*) ; 
 int /*<<< orphan*/  set_pageblock_migratetype (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_watermark_ok (struct zone*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __isolate_free_page(struct page *page, unsigned int order)
{
	unsigned long watermark;
	struct zone *zone;
	int mt;

	BUG_ON(!PageBuddy(page));

	zone = page_zone(page);
	mt = get_pageblock_migratetype(page);

	if (!is_migrate_isolate(mt)) {
		/*
		 * Obey watermarks as if the page was being allocated. We can
		 * emulate a high-order watermark check with a raised order-0
		 * watermark, because we already know our high-order page
		 * exists.
		 */
		watermark = min_wmark_pages(zone) + (1UL << order);
		if (!zone_watermark_ok(zone, 0, watermark, 0, ALLOC_CMA))
			return 0;

		__mod_zone_freepage_state(zone, -(1UL << order), mt);
	}

	/* Remove page from free list */
	list_del(&page->lru);
	zone->free_area[order].nr_free--;
	rmv_page_order(page);

	/*
	 * Set the pageblock if the isolated page is at least half of a
	 * pageblock
	 */
	if (order >= pageblock_order - 1) {
		struct page *endpage = page + (1 << order) - 1;
		for (; page < endpage; page += pageblock_nr_pages) {
			int mt = get_pageblock_migratetype(page);
			if (!is_migrate_isolate(mt) && !is_migrate_cma(mt)
			    && !is_migrate_highatomic(mt))
				set_pageblock_migratetype(page,
							  MIGRATE_MOVABLE);
		}
	}


	return 1UL << order;
}