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
struct page {int /*<<< orphan*/  flags; int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  ISOLATE_UNEVICTABLE ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIGRATE_SYNC ; 
 int /*<<< orphan*/  MPOL_MF_MOVE_ALL ; 
 int /*<<< orphan*/  MR_MEMORY_FAILURE ; 
 scalar_t__ NR_ISOLATED_ANON ; 
 scalar_t__ PageHWPoison (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  SetPageHWPoison (struct page*) ; 
 int /*<<< orphan*/  __PageMovable (struct page*) ; 
 int /*<<< orphan*/  inc_node_page_state (struct page*,scalar_t__) ; 
 int invalidate_inode_page (struct page*) ; 
 int isolate_lru_page (struct page*) ; 
 int isolate_movable_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int migrate_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_page ; 
 int /*<<< orphan*/  num_poisoned_pages_inc () ; 
 int /*<<< orphan*/  page_count (struct page*) ; 
 scalar_t__ page_is_file_cache (struct page*) ; 
 unsigned long page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pagelist ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long,...) ; 
 int /*<<< orphan*/  put_hwpoison_page (struct page*) ; 
 int /*<<< orphan*/  putback_movable_pages (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

__attribute__((used)) static int __soft_offline_page(struct page *page, int flags)
{
	int ret;
	unsigned long pfn = page_to_pfn(page);

	/*
	 * Check PageHWPoison again inside page lock because PageHWPoison
	 * is set by memory_failure() outside page lock. Note that
	 * memory_failure() also double-checks PageHWPoison inside page lock,
	 * so there's no race between soft_offline_page() and memory_failure().
	 */
	lock_page(page);
	wait_on_page_writeback(page);
	if (PageHWPoison(page)) {
		unlock_page(page);
		put_hwpoison_page(page);
		pr_info("soft offline: %#lx page already poisoned\n", pfn);
		return -EBUSY;
	}
	/*
	 * Try to invalidate first. This should work for
	 * non dirty unmapped page cache pages.
	 */
	ret = invalidate_inode_page(page);
	unlock_page(page);
	/*
	 * RED-PEN would be better to keep it isolated here, but we
	 * would need to fix isolation locking first.
	 */
	if (ret == 1) {
		put_hwpoison_page(page);
		pr_info("soft_offline: %#lx: invalidated\n", pfn);
		SetPageHWPoison(page);
		num_poisoned_pages_inc();
		return 0;
	}

	/*
	 * Simple invalidation didn't work.
	 * Try to migrate to a new page instead. migrate.c
	 * handles a large number of cases for us.
	 */
	if (PageLRU(page))
		ret = isolate_lru_page(page);
	else
		ret = isolate_movable_page(page, ISOLATE_UNEVICTABLE);
	/*
	 * Drop page reference which is came from get_any_page()
	 * successful isolate_lru_page() already took another one.
	 */
	put_hwpoison_page(page);
	if (!ret) {
		LIST_HEAD(pagelist);
		/*
		 * After isolated lru page, the PageLRU will be cleared,
		 * so use !__PageMovable instead for LRU page's mapping
		 * cannot have PAGE_MAPPING_MOVABLE.
		 */
		if (!__PageMovable(page))
			inc_node_page_state(page, NR_ISOLATED_ANON +
						page_is_file_cache(page));
		list_add(&page->lru, &pagelist);
		ret = migrate_pages(&pagelist, new_page, NULL, MPOL_MF_MOVE_ALL,
					MIGRATE_SYNC, MR_MEMORY_FAILURE);
		if (ret) {
			if (!list_empty(&pagelist))
				putback_movable_pages(&pagelist);

			pr_info("soft offline: %#lx: migration failed %d, type %lx (%pGp)\n",
				pfn, ret, page->flags, &page->flags);
			if (ret > 0)
				ret = -EIO;
		}
	} else {
		pr_info("soft offline: %#lx: isolation failed: %d, page count %d, type %lx (%pGp)\n",
			pfn, ret, page_count(page), page->flags, &page->flags);
	}
	return ret;
}