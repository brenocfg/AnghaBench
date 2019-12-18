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
struct zone {TYPE_1__* zone_pgdat; } ;
struct pagevec {struct page** pages; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lru_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_MLOCK ; 
 scalar_t__ TestClearPageMlocked (struct page*) ; 
 int /*<<< orphan*/  __mod_zone_page_state (struct zone*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ __munlock_isolate_lru_page (struct page*,int) ; 
 int /*<<< orphan*/  __munlock_isolated_page (struct page*) ; 
 int /*<<< orphan*/  __munlock_isolation_failed (struct page*) ; 
 int /*<<< orphan*/  __putback_lru_fast (struct pagevec*,int) ; 
 int /*<<< orphan*/  __putback_lru_fast_prepare (struct page*,struct pagevec*,int*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  pagevec_add (struct pagevec*,struct page*) ; 
 int pagevec_count (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void __munlock_pagevec(struct pagevec *pvec, struct zone *zone)
{
	int i;
	int nr = pagevec_count(pvec);
	int delta_munlocked = -nr;
	struct pagevec pvec_putback;
	int pgrescued = 0;

	pagevec_init(&pvec_putback);

	/* Phase 1: page isolation */
	spin_lock_irq(&zone->zone_pgdat->lru_lock);
	for (i = 0; i < nr; i++) {
		struct page *page = pvec->pages[i];

		if (TestClearPageMlocked(page)) {
			/*
			 * We already have pin from follow_page_mask()
			 * so we can spare the get_page() here.
			 */
			if (__munlock_isolate_lru_page(page, false))
				continue;
			else
				__munlock_isolation_failed(page);
		} else {
			delta_munlocked++;
		}

		/*
		 * We won't be munlocking this page in the next phase
		 * but we still need to release the follow_page_mask()
		 * pin. We cannot do it under lru_lock however. If it's
		 * the last pin, __page_cache_release() would deadlock.
		 */
		pagevec_add(&pvec_putback, pvec->pages[i]);
		pvec->pages[i] = NULL;
	}
	__mod_zone_page_state(zone, NR_MLOCK, delta_munlocked);
	spin_unlock_irq(&zone->zone_pgdat->lru_lock);

	/* Now we can release pins of pages that we are not munlocking */
	pagevec_release(&pvec_putback);

	/* Phase 2: page munlock */
	for (i = 0; i < nr; i++) {
		struct page *page = pvec->pages[i];

		if (page) {
			lock_page(page);
			if (!__putback_lru_fast_prepare(page, &pvec_putback,
					&pgrescued)) {
				/*
				 * Slow path. We don't want to lose the last
				 * pin before unlock_page()
				 */
				get_page(page); /* for putback_lru_page() */
				__munlock_isolated_page(page);
				unlock_page(page);
				put_page(page); /* from follow_page_mask() */
			}
		}
	}

	/*
	 * Phase 3: page putback for pages that qualified for the fast path
	 * This will also call put_page() to return pin from follow_page_mask()
	 */
	if (pagevec_count(&pvec_putback))
		__putback_lru_fast(&pvec_putback, pgrescued);
}