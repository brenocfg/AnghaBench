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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NR_MLOCK ; 
 scalar_t__ PageCompound (struct page*) ; 
 scalar_t__ PageDoubleMap (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int PageTail (struct page*) ; 
 int /*<<< orphan*/  TestSetPageMlocked (struct page*) ; 
 int /*<<< orphan*/  UNEVICTABLE_PGMLOCKED ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  isolate_lru_page (struct page*) ; 
 int /*<<< orphan*/  mod_zone_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_zone (struct page*) ; 
 int /*<<< orphan*/  putback_lru_page (struct page*) ; 

void mlock_vma_page(struct page *page)
{
	/* Serialize with page migration */
	BUG_ON(!PageLocked(page));

	VM_BUG_ON_PAGE(PageTail(page), page);
	VM_BUG_ON_PAGE(PageCompound(page) && PageDoubleMap(page), page);

	if (!TestSetPageMlocked(page)) {
		mod_zone_page_state(page_zone(page), NR_MLOCK,
				    hpage_nr_pages(page));
		count_vm_event(UNEVICTABLE_PGMLOCKED);
		if (!isolate_lru_page(page))
			putback_lru_page(page);
	}
}