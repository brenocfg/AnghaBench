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
struct page {long flags; scalar_t__ mapping; scalar_t__ index; int /*<<< orphan*/  _mapcount; } ;
struct lruvec {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 long PAGE_FLAGS_CHECK_AT_PREP ; 
 long PG_active ; 
 long PG_dirty ; 
 long PG_locked ; 
 long PG_mlocked ; 
 long PG_referenced ; 
 long PG_swapbacked ; 
 long PG_swapcache ; 
 long PG_unevictable ; 
 long PG_uptodate ; 
 long PG_workingset ; 
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 scalar_t__ TAIL_MAPPING ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_compound_head (struct page*) ; 
 int /*<<< orphan*/  lru_add_page_tail (struct page*,struct page*,struct lruvec*,struct list_head*) ; 
 int /*<<< orphan*/  page_cpupid_last (struct page*) ; 
 int /*<<< orphan*/  page_cpupid_xchg_last (struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ page_is_idle (struct page*) ; 
 scalar_t__ page_is_young (struct page*) ; 
 int /*<<< orphan*/  page_ref_unfreeze (struct page*,int) ; 
 int /*<<< orphan*/  set_page_idle (struct page*) ; 
 int /*<<< orphan*/  set_page_young (struct page*) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void __split_huge_page_tail(struct page *head, int tail,
		struct lruvec *lruvec, struct list_head *list)
{
	struct page *page_tail = head + tail;

	VM_BUG_ON_PAGE(atomic_read(&page_tail->_mapcount) != -1, page_tail);

	/*
	 * Clone page flags before unfreezing refcount.
	 *
	 * After successful get_page_unless_zero() might follow flags change,
	 * for exmaple lock_page() which set PG_waiters.
	 */
	page_tail->flags &= ~PAGE_FLAGS_CHECK_AT_PREP;
	page_tail->flags |= (head->flags &
			((1L << PG_referenced) |
			 (1L << PG_swapbacked) |
			 (1L << PG_swapcache) |
			 (1L << PG_mlocked) |
			 (1L << PG_uptodate) |
			 (1L << PG_active) |
			 (1L << PG_workingset) |
			 (1L << PG_locked) |
			 (1L << PG_unevictable) |
			 (1L << PG_dirty)));

	/* ->mapping in first tail page is compound_mapcount */
	VM_BUG_ON_PAGE(tail > 2 && page_tail->mapping != TAIL_MAPPING,
			page_tail);
	page_tail->mapping = head->mapping;
	page_tail->index = head->index + tail;

	/* Page flags must be visible before we make the page non-compound. */
	smp_wmb();

	/*
	 * Clear PageTail before unfreezing page refcount.
	 *
	 * After successful get_page_unless_zero() might follow put_page()
	 * which needs correct compound_head().
	 */
	clear_compound_head(page_tail);

	/* Finally unfreeze refcount. Additional reference from page cache. */
	page_ref_unfreeze(page_tail, 1 + (!PageAnon(head) ||
					  PageSwapCache(head)));

	if (page_is_young(head))
		set_page_young(page_tail);
	if (page_is_idle(head))
		set_page_idle(page_tail);

	page_cpupid_xchg_last(page_tail, page_cpupid_last(head));

	/*
	 * always add to the tail because some iterators expect new
	 * pages to show after the currently processed elements - e.g.
	 * migrate_pages
	 */
	lru_add_page_tail(head, page_tail, lruvec, list);
}