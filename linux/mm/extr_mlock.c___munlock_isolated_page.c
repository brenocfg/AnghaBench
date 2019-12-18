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
 int /*<<< orphan*/  PageMlocked (struct page*) ; 
 int /*<<< orphan*/  UNEVICTABLE_PGMUNLOCKED ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int page_mapcount (struct page*) ; 
 int /*<<< orphan*/  putback_lru_page (struct page*) ; 
 int /*<<< orphan*/  try_to_munlock (struct page*) ; 

__attribute__((used)) static void __munlock_isolated_page(struct page *page)
{
	/*
	 * Optimization: if the page was mapped just once, that's our mapping
	 * and we don't need to check all the other vmas.
	 */
	if (page_mapcount(page) > 1)
		try_to_munlock(page);

	/* Did try_to_unlock() succeed or punt? */
	if (!PageMlocked(page))
		count_vm_event(UNEVICTABLE_PGMUNLOCKED);

	putback_lru_page(page);
}