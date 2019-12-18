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
struct zone {unsigned long nr_reserved_highatomic; int /*<<< orphan*/  lock; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIGRATE_HIGHATOMIC ; 
 int get_pageblock_migratetype (struct page*) ; 
 int /*<<< orphan*/  is_migrate_cma (int) ; 
 int /*<<< orphan*/  is_migrate_highatomic (int) ; 
 int /*<<< orphan*/  is_migrate_isolate (int) ; 
 int /*<<< orphan*/  move_freepages_block (struct zone*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pageblock_nr_pages ; 
 int /*<<< orphan*/  set_pageblock_migratetype (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int zone_managed_pages (struct zone*) ; 

__attribute__((used)) static void reserve_highatomic_pageblock(struct page *page, struct zone *zone,
				unsigned int alloc_order)
{
	int mt;
	unsigned long max_managed, flags;

	/*
	 * Limit the number reserved to 1 pageblock or roughly 1% of a zone.
	 * Check is race-prone but harmless.
	 */
	max_managed = (zone_managed_pages(zone) / 100) + pageblock_nr_pages;
	if (zone->nr_reserved_highatomic >= max_managed)
		return;

	spin_lock_irqsave(&zone->lock, flags);

	/* Recheck the nr_reserved_highatomic limit under the lock */
	if (zone->nr_reserved_highatomic >= max_managed)
		goto out_unlock;

	/* Yoink! */
	mt = get_pageblock_migratetype(page);
	if (!is_migrate_highatomic(mt) && !is_migrate_isolate(mt)
	    && !is_migrate_cma(mt)) {
		zone->nr_reserved_highatomic += pageblock_nr_pages;
		set_pageblock_migratetype(page, MIGRATE_HIGHATOMIC);
		move_freepages_block(zone, page, MIGRATE_HIGHATOMIC, NULL);
	}

out_unlock:
	spin_unlock_irqrestore(&zone->lock, flags);
}