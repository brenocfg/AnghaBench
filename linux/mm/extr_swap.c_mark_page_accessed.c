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
 int /*<<< orphan*/  ClearPageReferenced (struct page*) ; 
 int /*<<< orphan*/  PageActive (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 scalar_t__ PageReferenced (struct page*) ; 
 int /*<<< orphan*/  PageUnevictable (struct page*) ; 
 int /*<<< orphan*/  SetPageReferenced (struct page*) ; 
 int /*<<< orphan*/  __lru_cache_activate_page (struct page*) ; 
 int /*<<< orphan*/  activate_page (struct page*) ; 
 int /*<<< orphan*/  clear_page_idle (struct page*) ; 
 struct page* compound_head (struct page*) ; 
 scalar_t__ page_is_file_cache (struct page*) ; 
 scalar_t__ page_is_idle (struct page*) ; 
 int /*<<< orphan*/  workingset_activation (struct page*) ; 

void mark_page_accessed(struct page *page)
{
	page = compound_head(page);
	if (!PageActive(page) && !PageUnevictable(page) &&
			PageReferenced(page)) {

		/*
		 * If the page is on the LRU, queue it for activation via
		 * activate_page_pvecs. Otherwise, assume the page is on a
		 * pagevec, mark it active and it'll be moved to the active
		 * LRU on the next drain.
		 */
		if (PageLRU(page))
			activate_page(page);
		else
			__lru_cache_activate_page(page);
		ClearPageReferenced(page);
		if (page_is_file_cache(page))
			workingset_activation(page);
	} else if (!PageReferenced(page)) {
		SetPageReferenced(page);
	}
	if (page_is_idle(page))
		clear_page_idle(page);
}