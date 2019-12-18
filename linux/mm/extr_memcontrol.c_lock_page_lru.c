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
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  del_page_from_lru_list (struct page*,struct lruvec*,int /*<<< orphan*/ ) ; 
 struct lruvec* mem_cgroup_page_lruvec (struct page*,TYPE_1__*) ; 
 int /*<<< orphan*/  page_lru (struct page*) ; 
 TYPE_1__* page_pgdat (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lock_page_lru(struct page *page, int *isolated)
{
	pg_data_t *pgdat = page_pgdat(page);

	spin_lock_irq(&pgdat->lru_lock);
	if (PageLRU(page)) {
		struct lruvec *lruvec;

		lruvec = mem_cgroup_page_lruvec(page, pgdat);
		ClearPageLRU(page);
		del_page_from_lru_list(page, lruvec, page_lru(page));
		*isolated = 1;
	} else
		*isolated = 0;
}