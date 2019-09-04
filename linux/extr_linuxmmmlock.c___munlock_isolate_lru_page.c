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
 int /*<<< orphan*/  ClearPageLRU (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct page*,struct lruvec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct lruvec* mem_cgroup_page_lruvec (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_lru (struct page*) ; 
 int /*<<< orphan*/  page_pgdat (struct page*) ; 

__attribute__((used)) static bool __munlock_isolate_lru_page(struct page *page, bool getpage)
{
	if (PageLRU(page)) {
		struct lruvec *lruvec;

		lruvec = mem_cgroup_page_lruvec(page, page_pgdat(page));
		if (getpage)
			get_page(page);
		ClearPageLRU(page);
		del_page_from_lru_list(page, lruvec, page_lru(page));
		return true;
	}

	return false;
}