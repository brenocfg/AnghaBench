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
 int /*<<< orphan*/  NR_MLOCK ; 
 scalar_t__ PageUnevictable (struct page*) ; 
 int /*<<< orphan*/  TestClearPageMlocked (struct page*) ; 
 int /*<<< orphan*/  UNEVICTABLE_PGCLEARED ; 
 int /*<<< orphan*/  UNEVICTABLE_PGSTRANDED ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  isolate_lru_page (struct page*) ; 
 int /*<<< orphan*/  mod_zone_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_zone (struct page*) ; 
 int /*<<< orphan*/  putback_lru_page (struct page*) ; 

void clear_page_mlock(struct page *page)
{
	if (!TestClearPageMlocked(page))
		return;

	mod_zone_page_state(page_zone(page), NR_MLOCK,
			    -hpage_nr_pages(page));
	count_vm_event(UNEVICTABLE_PGCLEARED);
	/*
	 * The previous TestClearPageMlocked() corresponds to the smp_mb()
	 * in __pagevec_lru_add_fn().
	 *
	 * See __pagevec_lru_add_fn for more explanation.
	 */
	if (!isolate_lru_page(page)) {
		putback_lru_page(page);
	} else {
		/*
		 * We lost the race. the page already moved to evictable list.
		 */
		if (PageUnevictable(page))
			count_vm_event(UNEVICTABLE_PGSTRANDED);
	}
}