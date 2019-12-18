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
 int EBUSY ; 
 int MIGRATE_ISOLATE ; 
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 scalar_t__ PageHuge (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 int __soft_offline_page (struct page*,int) ; 
 struct page* compound_head (struct page*) ; 
 int get_pageblock_migratetype (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_hwpoison_page (struct page*) ; 
 int /*<<< orphan*/  set_pageblock_migratetype (struct page*,int) ; 
 int soft_offline_huge_page (struct page*,int) ; 
 int /*<<< orphan*/  split_huge_page (struct page*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int soft_offline_in_use_page(struct page *page, int flags)
{
	int ret;
	int mt;
	struct page *hpage = compound_head(page);

	if (!PageHuge(page) && PageTransHuge(hpage)) {
		lock_page(page);
		if (!PageAnon(page) || unlikely(split_huge_page(page))) {
			unlock_page(page);
			if (!PageAnon(page))
				pr_info("soft offline: %#lx: non anonymous thp\n", page_to_pfn(page));
			else
				pr_info("soft offline: %#lx: thp split failed\n", page_to_pfn(page));
			put_hwpoison_page(page);
			return -EBUSY;
		}
		unlock_page(page);
	}

	/*
	 * Setting MIGRATE_ISOLATE here ensures that the page will be linked
	 * to free list immediately (not via pcplist) when released after
	 * successful page migration. Otherwise we can't guarantee that the
	 * page is really free after put_page() returns, so
	 * set_hwpoison_free_buddy_page() highly likely fails.
	 */
	mt = get_pageblock_migratetype(page);
	set_pageblock_migratetype(page, MIGRATE_ISOLATE);
	if (PageHuge(page))
		ret = soft_offline_huge_page(page, flags);
	else
		ret = __soft_offline_page(page, flags);
	set_pageblock_migratetype(page, mt);
	return ret;
}