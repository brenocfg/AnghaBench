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
 scalar_t__ PageCompound (struct page*) ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageUnevictable (struct page*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  lru_rotate_pvecs ; 
 int /*<<< orphan*/  pagevec_add (struct pagevec*,struct page*) ; 
 int /*<<< orphan*/  pagevec_move_tail (struct pagevec*) ; 
 struct pagevec* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void rotate_reclaimable_page(struct page *page)
{
	if (!PageLocked(page) && !PageDirty(page) &&
	    !PageUnevictable(page) && PageLRU(page)) {
		struct pagevec *pvec;
		unsigned long flags;

		get_page(page);
		local_irq_save(flags);
		pvec = this_cpu_ptr(&lru_rotate_pvecs);
		if (!pagevec_add(pvec, page) || PageCompound(page))
			pagevec_move_tail(pvec);
		local_irq_restore(flags);
	}
}