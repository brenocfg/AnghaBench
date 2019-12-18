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
struct TYPE_4__ {int /*<<< orphan*/  lru_lock; } ;
typedef  TYPE_1__ pg_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  __activate_page (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_page_lruvec (struct page*,TYPE_1__*) ; 
 TYPE_1__* page_pgdat (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void activate_page(struct page *page)
{
	pg_data_t *pgdat = page_pgdat(page);

	page = compound_head(page);
	spin_lock_irq(&pgdat->lru_lock);
	__activate_page(page, mem_cgroup_page_lruvec(page, pgdat), NULL);
	spin_unlock_irq(&pgdat->lru_lock);
}