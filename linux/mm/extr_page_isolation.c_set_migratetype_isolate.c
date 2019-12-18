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
struct memory_isolate_notify {unsigned long start_pfn; scalar_t__ pages_found; int /*<<< orphan*/  nr_pages; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MEM_ISOLATE_COUNT ; 
 int /*<<< orphan*/  MIGRATE_ISOLATE ; 
 int /*<<< orphan*/  __mod_zone_freepage_state (struct zone*,unsigned long,int) ; 
 int /*<<< orphan*/  drain_all_pages (struct zone*) ; 
 int get_pageblock_migratetype (struct page*) ; 
 int /*<<< orphan*/  has_unmovable_pages (struct zone*,struct page*,scalar_t__,int,int) ; 
 scalar_t__ is_migrate_isolate_page (struct page*) ; 
 int memory_isolate_notify (int /*<<< orphan*/ ,struct memory_isolate_notify*) ; 
 unsigned long move_freepages_block (struct zone*,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int notifier_to_errno (int) ; 
 unsigned long page_to_pfn (struct page*) ; 
 struct zone* page_zone (struct page*) ; 
 int /*<<< orphan*/  pageblock_nr_pages ; 
 int /*<<< orphan*/  set_pageblock_migratetype (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int set_migratetype_isolate(struct page *page, int migratetype, int isol_flags)
{
	struct zone *zone;
	unsigned long flags, pfn;
	struct memory_isolate_notify arg;
	int notifier_ret;
	int ret = -EBUSY;

	zone = page_zone(page);

	spin_lock_irqsave(&zone->lock, flags);

	/*
	 * We assume the caller intended to SET migrate type to isolate.
	 * If it is already set, then someone else must have raced and
	 * set it before us.  Return -EBUSY
	 */
	if (is_migrate_isolate_page(page))
		goto out;

	pfn = page_to_pfn(page);
	arg.start_pfn = pfn;
	arg.nr_pages = pageblock_nr_pages;
	arg.pages_found = 0;

	/*
	 * It may be possible to isolate a pageblock even if the
	 * migratetype is not MIGRATE_MOVABLE. The memory isolation
	 * notifier chain is used by balloon drivers to return the
	 * number of pages in a range that are held by the balloon
	 * driver to shrink memory. If all the pages are accounted for
	 * by balloons, are free, or on the LRU, isolation can continue.
	 * Later, for example, when memory hotplug notifier runs, these
	 * pages reported as "can be isolated" should be isolated(freed)
	 * by the balloon driver through the memory notifier chain.
	 */
	notifier_ret = memory_isolate_notify(MEM_ISOLATE_COUNT, &arg);
	notifier_ret = notifier_to_errno(notifier_ret);
	if (notifier_ret)
		goto out;
	/*
	 * FIXME: Now, memory hotplug doesn't call shrink_slab() by itself.
	 * We just check MOVABLE pages.
	 */
	if (!has_unmovable_pages(zone, page, arg.pages_found, migratetype,
				 isol_flags))
		ret = 0;

	/*
	 * immobile means "not-on-lru" pages. If immobile is larger than
	 * removable-by-driver pages reported by notifier, we'll fail.
	 */

out:
	if (!ret) {
		unsigned long nr_pages;
		int mt = get_pageblock_migratetype(page);

		set_pageblock_migratetype(page, MIGRATE_ISOLATE);
		zone->nr_isolate_pageblock++;
		nr_pages = move_freepages_block(zone, page, MIGRATE_ISOLATE,
									NULL);

		__mod_zone_freepage_state(zone, -nr_pages, mt);
	}

	spin_unlock_irqrestore(&zone->lock, flags);
	if (!ret)
		drain_all_pages(zone);
	return ret;
}