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
struct pagevec {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ TestClearPageUnevictable (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 scalar_t__ page_evictable (struct page*) ; 
 int page_mapcount (struct page*) ; 
 int /*<<< orphan*/  pagevec_add (struct pagevec*,struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static bool __putback_lru_fast_prepare(struct page *page, struct pagevec *pvec,
		int *pgrescued)
{
	VM_BUG_ON_PAGE(PageLRU(page), page);
	VM_BUG_ON_PAGE(!PageLocked(page), page);

	if (page_mapcount(page) <= 1 && page_evictable(page)) {
		pagevec_add(pvec, page);
		if (TestClearPageUnevictable(page))
			(*pgrescued)++;
		unlock_page(page);
		return true;
	}

	return false;
}