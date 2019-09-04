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
struct zone {int /*<<< orphan*/  lock; int /*<<< orphan*/  nr_isolate_pageblock; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageBuddy (struct page*) ; 
 int /*<<< orphan*/  __GFP_MOVABLE ; 
 unsigned long __find_buddy_pfn (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  __free_pages (struct page*,unsigned int) ; 
 int /*<<< orphan*/  __isolate_free_page (struct page*,unsigned int) ; 
 int /*<<< orphan*/  __mod_zone_freepage_state (struct zone*,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  is_migrate_isolate_page (struct page*) ; 
 unsigned long move_freepages_block (struct zone*,struct page*,unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int page_order (struct page*) ; 
 unsigned long page_to_pfn (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 unsigned int pageblock_order ; 
 scalar_t__ pfn_valid_within (unsigned long) ; 
 int /*<<< orphan*/  post_alloc_hook (struct page*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pageblock_migratetype (struct page*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void unset_migratetype_isolate(struct page *page, unsigned migratetype)
{
	struct zone *zone;
	unsigned long flags, nr_pages;
	bool isolated_page = false;
	unsigned int order;
	unsigned long pfn, buddy_pfn;
	struct page *buddy;

	zone = page_zone(page);
	spin_lock_irqsave(&zone->lock, flags);
	if (!is_migrate_isolate_page(page))
		goto out;

	/*
	 * Because freepage with more than pageblock_order on isolated
	 * pageblock is restricted to merge due to freepage counting problem,
	 * it is possible that there is free buddy page.
	 * move_freepages_block() doesn't care of merge so we need other
	 * approach in order to merge them. Isolation and free will make
	 * these pages to be merged.
	 */
	if (PageBuddy(page)) {
		order = page_order(page);
		if (order >= pageblock_order) {
			pfn = page_to_pfn(page);
			buddy_pfn = __find_buddy_pfn(pfn, order);
			buddy = page + (buddy_pfn - pfn);

			if (pfn_valid_within(buddy_pfn) &&
			    !is_migrate_isolate_page(buddy)) {
				__isolate_free_page(page, order);
				isolated_page = true;
			}
		}
	}

	/*
	 * If we isolate freepage with more than pageblock_order, there
	 * should be no freepage in the range, so we could avoid costly
	 * pageblock scanning for freepage moving.
	 */
	if (!isolated_page) {
		nr_pages = move_freepages_block(zone, page, migratetype, NULL);
		__mod_zone_freepage_state(zone, nr_pages, migratetype);
	}
	set_pageblock_migratetype(page, migratetype);
	zone->nr_isolate_pageblock--;
out:
	spin_unlock_irqrestore(&zone->lock, flags);
	if (isolated_page) {
		post_alloc_hook(page, order, __GFP_MOVABLE);
		__free_pages(page, order);
	}
}