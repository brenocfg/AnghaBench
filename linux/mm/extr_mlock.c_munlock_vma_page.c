#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  lru_lock; } ;
typedef  TYPE_1__ pg_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NR_MLOCK ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageTail (struct page*) ; 
 int /*<<< orphan*/  TestClearPageMlocked (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  __mod_zone_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ __munlock_isolate_lru_page (struct page*,int) ; 
 int /*<<< orphan*/  __munlock_isolated_page (struct page*) ; 
 int /*<<< orphan*/  __munlock_isolation_failed (struct page*) ; 
 int hpage_nr_pages (struct page*) ; 
 TYPE_1__* page_pgdat (struct page*) ; 
 int /*<<< orphan*/  page_zone (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

unsigned int munlock_vma_page(struct page *page)
{
	int nr_pages;
	pg_data_t *pgdat = page_pgdat(page);

	/* For try_to_munlock() and to serialize with page migration */
	BUG_ON(!PageLocked(page));

	VM_BUG_ON_PAGE(PageTail(page), page);

	/*
	 * Serialize with any parallel __split_huge_page_refcount() which
	 * might otherwise copy PageMlocked to part of the tail pages before
	 * we clear it in the head page. It also stabilizes hpage_nr_pages().
	 */
	spin_lock_irq(&pgdat->lru_lock);

	if (!TestClearPageMlocked(page)) {
		/* Potentially, PTE-mapped THP: do not skip the rest PTEs */
		nr_pages = 1;
		goto unlock_out;
	}

	nr_pages = hpage_nr_pages(page);
	__mod_zone_page_state(page_zone(page), NR_MLOCK, -nr_pages);

	if (__munlock_isolate_lru_page(page, true)) {
		spin_unlock_irq(&pgdat->lru_lock);
		__munlock_isolated_page(page);
		goto out;
	}
	__munlock_isolation_failed(page);

unlock_out:
	spin_unlock_irq(&pgdat->lru_lock);

out:
	return nr_pages - 1;
}