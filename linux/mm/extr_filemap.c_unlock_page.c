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
struct page {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  PG_locked ; 
 int PG_waiters ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 scalar_t__ clear_bit_unlock_is_negative_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  wake_up_page_bit (struct page*,int /*<<< orphan*/ ) ; 

void unlock_page(struct page *page)
{
	BUILD_BUG_ON(PG_waiters != 7);
	page = compound_head(page);
	VM_BUG_ON_PAGE(!PageLocked(page), page);
	if (clear_bit_unlock_is_negative_byte(PG_locked, &page->flags))
		wake_up_page_bit(page, PG_locked);
}