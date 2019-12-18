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
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  ClearPageReclaim (struct page*) ; 
 int /*<<< orphan*/  PG_writeback ; 
 scalar_t__ PageReclaim (struct page*) ; 
 int /*<<< orphan*/  rotate_reclaimable_page (struct page*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  test_clear_page_writeback (struct page*) ; 
 int /*<<< orphan*/  wake_up_page (struct page*,int /*<<< orphan*/ ) ; 

void end_page_writeback(struct page *page)
{
	/*
	 * TestClearPageReclaim could be used here but it is an atomic
	 * operation and overkill in this particular case. Failing to
	 * shuffle a page marked for immediate reclaim is too mild to
	 * justify taking an atomic operation penalty at the end of
	 * ever page writeback.
	 */
	if (PageReclaim(page)) {
		ClearPageReclaim(page);
		rotate_reclaimable_page(page);
	}

	if (!test_clear_page_writeback(page))
		BUG();

	smp_mb__after_atomic();
	wake_up_page(page, PG_writeback);
}