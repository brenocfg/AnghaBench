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
struct zone {unsigned long* _watermark; struct free_area* free_area; } ;
struct page {int dummy; } ;
struct free_area {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_CMA ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  MIGRATE_MOVABLE ; 
 int /*<<< orphan*/  PageBuddy (struct page*) ; 
 size_t WMARK_MIN ; 
 int /*<<< orphan*/  __mod_zone_freepage_state (struct zone*,unsigned long,int) ; 
 int /*<<< orphan*/  del_page_from_free_area (struct page*,struct free_area*) ; 
 int get_pageblock_migratetype (struct page*) ; 
 int /*<<< orphan*/  is_migrate_cma (int) ; 
 int /*<<< orphan*/  is_migrate_highatomic (int) ; 
 int /*<<< orphan*/  is_migrate_isolate (int) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  pageblock_nr_pages ; 
 int pageblock_order ; 
 int /*<<< orphan*/  set_pageblock_migratetype (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_watermark_ok (struct zone*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __isolate_free_page(struct page *page, unsigned int order)
{
	struct free_area *area = &page_zone(page)->free_area[order];
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
		watermark = zone->_watermark[WMARK_MIN] + (1UL << order);
		if (!zone_watermark_ok(zone, 0, watermark, 0, ALLOC_CMA))
			return 0;

		__mod_zone_freepage_state(zone, -(1UL << order), mt);
	}

	/* Remove page from free list */

	del_page_from_free_area(page, area);

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