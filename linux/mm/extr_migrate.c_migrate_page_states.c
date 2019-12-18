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
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  ClearPageSwapCache (struct page*) ; 
 scalar_t__ PageChecked (struct page*) ; 
 scalar_t__ PageDirty (struct page*) ; 
 scalar_t__ PageError (struct page*) ; 
 scalar_t__ PageMappedToDisk (struct page*) ; 
 scalar_t__ PageReferenced (struct page*) ; 
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  PageUnevictable (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 scalar_t__ PageWorkingset (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  SetPageActive (struct page*) ; 
 int /*<<< orphan*/  SetPageChecked (struct page*) ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 int /*<<< orphan*/  SetPageError (struct page*) ; 
 int /*<<< orphan*/  SetPageMappedToDisk (struct page*) ; 
 int /*<<< orphan*/  SetPageReferenced (struct page*) ; 
 int /*<<< orphan*/  SetPageUnevictable (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int /*<<< orphan*/  SetPageWorkingset (struct page*) ; 
 scalar_t__ TestClearPageActive (struct page*) ; 
 scalar_t__ TestClearPageUnevictable (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  copy_page_owner (struct page*,struct page*) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  ksm_migrate_page (struct page*,struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_migrate (struct page*,struct page*) ; 
 int page_cpupid_xchg_last (struct page*,int) ; 
 scalar_t__ page_is_idle (struct page*) ; 
 scalar_t__ page_is_young (struct page*) ; 
 int /*<<< orphan*/  set_page_idle (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_young (struct page*) ; 

void migrate_page_states(struct page *newpage, struct page *page)
{
	int cpupid;

	if (PageError(page))
		SetPageError(newpage);
	if (PageReferenced(page))
		SetPageReferenced(newpage);
	if (PageUptodate(page))
		SetPageUptodate(newpage);
	if (TestClearPageActive(page)) {
		VM_BUG_ON_PAGE(PageUnevictable(page), page);
		SetPageActive(newpage);
	} else if (TestClearPageUnevictable(page))
		SetPageUnevictable(newpage);
	if (PageWorkingset(page))
		SetPageWorkingset(newpage);
	if (PageChecked(page))
		SetPageChecked(newpage);
	if (PageMappedToDisk(page))
		SetPageMappedToDisk(newpage);

	/* Move dirty on pages not done by migrate_page_move_mapping() */
	if (PageDirty(page))
		SetPageDirty(newpage);

	if (page_is_young(page))
		set_page_young(newpage);
	if (page_is_idle(page))
		set_page_idle(newpage);

	/*
	 * Copy NUMA information to the new page, to prevent over-eager
	 * future migrations of this same page.
	 */
	cpupid = page_cpupid_xchg_last(page, -1);
	page_cpupid_xchg_last(newpage, cpupid);

	ksm_migrate_page(newpage, page);
	/*
	 * Please do not reorder this without considering how mm/ksm.c's
	 * get_ksm_page() depends upon ksm_migrate_page() and PageSwapCache().
	 */
	if (PageSwapCache(page))
		ClearPageSwapCache(page);
	ClearPagePrivate(page);
	set_page_private(page, 0);

	/*
	 * If any waiters have accumulated on the new page then
	 * wake them up.
	 */
	if (PageWriteback(newpage))
		end_page_writeback(newpage);

	copy_page_owner(page, newpage);

	mem_cgroup_migrate(page, newpage);
}