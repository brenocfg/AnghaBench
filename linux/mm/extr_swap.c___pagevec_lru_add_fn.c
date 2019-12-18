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
struct lruvec {int dummy; } ;
typedef  enum lru_list { ____Placeholder_lru_list } lru_list ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageActive (struct page*) ; 
 int LRU_UNEVICTABLE ; 
 int /*<<< orphan*/  PageActive (struct page*) ; 
 int /*<<< orphan*/  PageLRU (struct page*) ; 
 int /*<<< orphan*/  SetPageLRU (struct page*) ; 
 int /*<<< orphan*/  SetPageUnevictable (struct page*) ; 
 int TestClearPageUnevictable (struct page*) ; 
 int /*<<< orphan*/  UNEVICTABLE_PGCULLED ; 
 int /*<<< orphan*/  UNEVICTABLE_PGRESCUED ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  add_page_to_lru_list (struct page*,struct lruvec*,int) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 scalar_t__ page_evictable (struct page*) ; 
 int /*<<< orphan*/  page_is_file_cache (struct page*) ; 
 int page_lru (struct page*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  trace_mm_lru_insertion (struct page*,int) ; 
 int /*<<< orphan*/  update_page_reclaim_stat (struct lruvec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __pagevec_lru_add_fn(struct page *page, struct lruvec *lruvec,
				 void *arg)
{
	enum lru_list lru;
	int was_unevictable = TestClearPageUnevictable(page);

	VM_BUG_ON_PAGE(PageLRU(page), page);

	SetPageLRU(page);
	/*
	 * Page becomes evictable in two ways:
	 * 1) Within LRU lock [munlock_vma_page() and __munlock_pagevec()].
	 * 2) Before acquiring LRU lock to put the page to correct LRU and then
	 *   a) do PageLRU check with lock [check_move_unevictable_pages]
	 *   b) do PageLRU check before lock [clear_page_mlock]
	 *
	 * (1) & (2a) are ok as LRU lock will serialize them. For (2b), we need
	 * following strict ordering:
	 *
	 * #0: __pagevec_lru_add_fn		#1: clear_page_mlock
	 *
	 * SetPageLRU()				TestClearPageMlocked()
	 * smp_mb() // explicit ordering	// above provides strict
	 *					// ordering
	 * PageMlocked()			PageLRU()
	 *
	 *
	 * if '#1' does not observe setting of PG_lru by '#0' and fails
	 * isolation, the explicit barrier will make sure that page_evictable
	 * check will put the page in correct LRU. Without smp_mb(), SetPageLRU
	 * can be reordered after PageMlocked check and can make '#1' to fail
	 * the isolation of the page whose Mlocked bit is cleared (#0 is also
	 * looking at the same page) and the evictable page will be stranded
	 * in an unevictable LRU.
	 */
	smp_mb();

	if (page_evictable(page)) {
		lru = page_lru(page);
		update_page_reclaim_stat(lruvec, page_is_file_cache(page),
					 PageActive(page));
		if (was_unevictable)
			count_vm_event(UNEVICTABLE_PGRESCUED);
	} else {
		lru = LRU_UNEVICTABLE;
		ClearPageActive(page);
		SetPageUnevictable(page);
		if (!was_unevictable)
			count_vm_event(UNEVICTABLE_PGCULLED);
	}

	add_page_to_lru_list(page, lruvec, lru);
	trace_mm_lru_insertion(page, lru);
}