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
struct zone {int /*<<< orphan*/  flags; int /*<<< orphan*/  lock; } ;
struct page {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 unsigned int ALLOC_HARDER ; 
 int /*<<< orphan*/  MIGRATE_HIGHATOMIC ; 
 int /*<<< orphan*/  PGALLOC ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ZONE_BOOSTED_WATERMARK ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  __count_zid_vm_events (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __mod_zone_freepage_state (struct zone*,int,int /*<<< orphan*/ ) ; 
 struct page* __rmqueue (struct zone*,unsigned int,int,unsigned int) ; 
 struct page* __rmqueue_smallest (struct zone*,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ bad_range (struct zone*,struct page*) ; 
 scalar_t__ check_new_pages (struct page*,unsigned int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_pcppage_migratetype (struct page*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  page_zonenum (struct page*) ; 
 struct page* rmqueue_pcplist (struct zone*,struct zone*,int,int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mm_page_alloc_zone_locked (struct page*,unsigned int,int) ; 
 int /*<<< orphan*/  wakeup_kswapd (struct zone*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_idx (struct zone*) ; 
 int /*<<< orphan*/  zone_statistics (struct zone*,struct zone*) ; 

__attribute__((used)) static inline
struct page *rmqueue(struct zone *preferred_zone,
			struct zone *zone, unsigned int order,
			gfp_t gfp_flags, unsigned int alloc_flags,
			int migratetype)
{
	unsigned long flags;
	struct page *page;

	if (likely(order == 0)) {
		page = rmqueue_pcplist(preferred_zone, zone, gfp_flags,
					migratetype, alloc_flags);
		goto out;
	}

	/*
	 * We most definitely don't want callers attempting to
	 * allocate greater than order-1 page units with __GFP_NOFAIL.
	 */
	WARN_ON_ONCE((gfp_flags & __GFP_NOFAIL) && (order > 1));
	spin_lock_irqsave(&zone->lock, flags);

	do {
		page = NULL;
		if (alloc_flags & ALLOC_HARDER) {
			page = __rmqueue_smallest(zone, order, MIGRATE_HIGHATOMIC);
			if (page)
				trace_mm_page_alloc_zone_locked(page, order, migratetype);
		}
		if (!page)
			page = __rmqueue(zone, order, migratetype, alloc_flags);
	} while (page && check_new_pages(page, order));
	spin_unlock(&zone->lock);
	if (!page)
		goto failed;
	__mod_zone_freepage_state(zone, -(1 << order),
				  get_pcppage_migratetype(page));

	__count_zid_vm_events(PGALLOC, page_zonenum(page), 1 << order);
	zone_statistics(preferred_zone, zone);
	local_irq_restore(flags);

out:
	/* Separate test+clear to avoid unnecessary atomics */
	if (test_bit(ZONE_BOOSTED_WATERMARK, &zone->flags)) {
		clear_bit(ZONE_BOOSTED_WATERMARK, &zone->flags);
		wakeup_kswapd(zone, 0, 0, zone_idx(zone));
	}

	VM_BUG_ON_PAGE(page && bad_range(zone, page), page);
	return page;

failed:
	local_irq_restore(flags);
	return NULL;
}