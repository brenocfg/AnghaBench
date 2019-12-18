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
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  __ClearPageLRU (struct page*) ; 
 int /*<<< orphan*/  __ClearPageWaiters (struct page*) ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct page*,struct lruvec*,int /*<<< orphan*/ ) ; 
 struct lruvec* mem_cgroup_page_lruvec (struct page*,TYPE_1__*) ; 
 int /*<<< orphan*/  page_off_lru (struct page*) ; 
 TYPE_1__* page_pgdat (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void __page_cache_release(struct page *page)
{
	if (PageLRU(page)) {
		pg_data_t *pgdat = page_pgdat(page);
		struct lruvec *lruvec;
		unsigned long flags;

		spin_lock_irqsave(&pgdat->lru_lock, flags);
		lruvec = mem_cgroup_page_lruvec(page, pgdat);
		VM_BUG_ON_PAGE(!PageLRU(page), page);
		__ClearPageLRU(page);
		del_page_from_lru_list(page, lruvec, page_off_lru(page));
		spin_unlock_irqrestore(&pgdat->lru_lock, flags);
	}
	__ClearPageWaiters(page);
}