#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct lruvec {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  lru_lock; } ;
typedef  TYPE_1__ pg_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageLRU (struct page*) ; 
 int EBUSY ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageTail (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  WARN_RATELIMIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct page*,struct lruvec*,int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 struct lruvec* mem_cgroup_page_lruvec (struct page*,TYPE_1__*) ; 
 int /*<<< orphan*/  page_count (struct page*) ; 
 int page_lru (struct page*) ; 
 TYPE_1__* page_pgdat (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int isolate_lru_page(struct page *page)
{
	int ret = -EBUSY;

	VM_BUG_ON_PAGE(!page_count(page), page);
	WARN_RATELIMIT(PageTail(page), "trying to isolate tail page");

	if (PageLRU(page)) {
		pg_data_t *pgdat = page_pgdat(page);
		struct lruvec *lruvec;

		spin_lock_irq(&pgdat->lru_lock);
		lruvec = mem_cgroup_page_lruvec(page, pgdat);
		if (PageLRU(page)) {
			int lru = page_lru(page);
			get_page(page);
			ClearPageLRU(page);
			del_page_from_lru_list(page, lruvec, lru);
			ret = 0;
		}
		spin_unlock_irq(&pgdat->lru_lock);
	}
	return ret;
}