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
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIGRATE_SYNC ; 
 int /*<<< orphan*/  MPOL_MF_MOVE_ALL ; 
 int /*<<< orphan*/  MR_MEMORY_FAILURE ; 
 scalar_t__ PageHWPoison (struct page*) ; 
 struct page* compound_head (struct page*) ; 
 int dissolve_free_huge_page (struct page*) ; 
 int isolate_huge_page (struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int migrate_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_page ; 
 int /*<<< orphan*/  num_poisoned_pages_inc () ; 
 unsigned long page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pagelist ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long,...) ; 
 int /*<<< orphan*/  put_hwpoison_page (struct page*) ; 
 int /*<<< orphan*/  putback_movable_pages (int /*<<< orphan*/ *) ; 
 scalar_t__ set_hwpoison_free_buddy_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int soft_offline_huge_page(struct page *page, int flags)
{
	int ret;
	unsigned long pfn = page_to_pfn(page);
	struct page *hpage = compound_head(page);
	LIST_HEAD(pagelist);

	/*
	 * This double-check of PageHWPoison is to avoid the race with
	 * memory_failure(). See also comment in __soft_offline_page().
	 */
	lock_page(hpage);
	if (PageHWPoison(hpage)) {
		unlock_page(hpage);
		put_hwpoison_page(hpage);
		pr_info("soft offline: %#lx hugepage already poisoned\n", pfn);
		return -EBUSY;
	}
	unlock_page(hpage);

	ret = isolate_huge_page(hpage, &pagelist);
	/*
	 * get_any_page() and isolate_huge_page() takes a refcount each,
	 * so need to drop one here.
	 */
	put_hwpoison_page(hpage);
	if (!ret) {
		pr_info("soft offline: %#lx hugepage failed to isolate\n", pfn);
		return -EBUSY;
	}

	ret = migrate_pages(&pagelist, new_page, NULL, MPOL_MF_MOVE_ALL,
				MIGRATE_SYNC, MR_MEMORY_FAILURE);
	if (ret) {
		pr_info("soft offline: %#lx: hugepage migration failed %d, type %lx (%pGp)\n",
			pfn, ret, page->flags, &page->flags);
		if (!list_empty(&pagelist))
			putback_movable_pages(&pagelist);
		if (ret > 0)
			ret = -EIO;
	} else {
		/*
		 * We set PG_hwpoison only when the migration source hugepage
		 * was successfully dissolved, because otherwise hwpoisoned
		 * hugepage remains on free hugepage list, then userspace will
		 * find it as SIGBUS by allocation failure. That's not expected
		 * in soft-offlining.
		 */
		ret = dissolve_free_huge_page(page);
		if (!ret) {
			if (set_hwpoison_free_buddy_page(page))
				num_poisoned_pages_inc();
			else
				ret = -EBUSY;
		}
	}
	return ret;
}