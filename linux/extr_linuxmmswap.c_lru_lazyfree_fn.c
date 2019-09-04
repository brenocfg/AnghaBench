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

/* Variables and functions */
 int /*<<< orphan*/  ClearPageActive (struct page*) ; 
 int /*<<< orphan*/  ClearPageReferenced (struct page*) ; 
 int /*<<< orphan*/  ClearPageSwapBacked (struct page*) ; 
 scalar_t__ LRU_INACTIVE_ANON ; 
 int /*<<< orphan*/  LRU_INACTIVE_FILE ; 
 int /*<<< orphan*/  PGLAZYFREE ; 
 int PageActive (struct page*) ; 
 scalar_t__ PageAnon (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 scalar_t__ PageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  PageUnevictable (struct page*) ; 
 int /*<<< orphan*/  __count_vm_events (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_page_to_lru_list (struct page*,struct lruvec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_memcg_page_event (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct page*,struct lruvec*,scalar_t__) ; 
 int /*<<< orphan*/  hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  update_page_reclaim_stat (struct lruvec*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lru_lazyfree_fn(struct page *page, struct lruvec *lruvec,
			    void *arg)
{
	if (PageLRU(page) && PageAnon(page) && PageSwapBacked(page) &&
	    !PageSwapCache(page) && !PageUnevictable(page)) {
		bool active = PageActive(page);

		del_page_from_lru_list(page, lruvec,
				       LRU_INACTIVE_ANON + active);
		ClearPageActive(page);
		ClearPageReferenced(page);
		/*
		 * lazyfree pages are clean anonymous pages. They have
		 * SwapBacked flag cleared to distinguish normal anonymous
		 * pages
		 */
		ClearPageSwapBacked(page);
		add_page_to_lru_list(page, lruvec, LRU_INACTIVE_FILE);

		__count_vm_events(PGLAZYFREE, hpage_nr_pages(page));
		count_memcg_page_event(page, PGLAZYFREE);
		update_page_reclaim_stat(lruvec, 1, 0);
	}
}