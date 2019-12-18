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
struct page {unsigned long flags; int /*<<< orphan*/ * mapping; } ;
struct dev_pagemap {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENXIO ; 
 int MF_COUNT_INCREASED ; 
 int /*<<< orphan*/  MF_DELAYED ; 
 int /*<<< orphan*/  MF_IGNORED ; 
 int /*<<< orphan*/  MF_MSG_BUDDY ; 
 int /*<<< orphan*/  MF_MSG_BUDDY_2ND ; 
 int /*<<< orphan*/  MF_MSG_DIFFERENT_COMPOUND ; 
 int /*<<< orphan*/  MF_MSG_KERNEL_HIGH_ORDER ; 
 int /*<<< orphan*/  MF_MSG_TRUNCATED_LRU ; 
 int /*<<< orphan*/  MF_MSG_UNMAP_FAILED ; 
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 scalar_t__ PageCompound (struct page*) ; 
 int /*<<< orphan*/  PageHWPoison (struct page*) ; 
 scalar_t__ PageHuge (struct page*) ; 
 scalar_t__ PageLRU (struct page*) ; 
 int /*<<< orphan*/  PageSwapCache (struct page*) ; 
 scalar_t__ PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  PageTransTail (struct page*) ; 
 scalar_t__ TestClearPageHWPoison (struct page*) ; 
 scalar_t__ TestSetPageHWPoison (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  action_result (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* compound_head (struct page*) ; 
 struct dev_pagemap* get_dev_pagemap (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_hwpoison_page (struct page*) ; 
 scalar_t__ hwpoison_filter (struct page*) ; 
 int /*<<< orphan*/  hwpoison_user_mappings (struct page*,unsigned long,int,struct page**) ; 
 int identify_page_state (unsigned long,struct page*,unsigned long) ; 
 scalar_t__ is_free_buddy_page (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int memory_failure_dev_pagemap (unsigned long,int,struct dev_pagemap*) ; 
 int memory_failure_hugetlb (unsigned long,int) ; 
 int /*<<< orphan*/  num_poisoned_pages_dec () ; 
 int /*<<< orphan*/  num_poisoned_pages_inc () ; 
 int /*<<< orphan*/  page_count (struct page*) ; 
 int /*<<< orphan*/  panic (char*,unsigned long) ; 
 struct page* pfn_to_online_page (unsigned long) ; 
 scalar_t__ pfn_valid (unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long) ; 
 int /*<<< orphan*/  put_hwpoison_page (struct page*) ; 
 int /*<<< orphan*/  shake_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  split_huge_page (struct page*) ; 
 int /*<<< orphan*/  sysctl_memory_failure_recovery ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

int memory_failure(unsigned long pfn, int flags)
{
	struct page *p;
	struct page *hpage;
	struct page *orig_head;
	struct dev_pagemap *pgmap;
	int res;
	unsigned long page_flags;

	if (!sysctl_memory_failure_recovery)
		panic("Memory failure on page %lx", pfn);

	p = pfn_to_online_page(pfn);
	if (!p) {
		if (pfn_valid(pfn)) {
			pgmap = get_dev_pagemap(pfn, NULL);
			if (pgmap)
				return memory_failure_dev_pagemap(pfn, flags,
								  pgmap);
		}
		pr_err("Memory failure: %#lx: memory outside kernel control\n",
			pfn);
		return -ENXIO;
	}

	if (PageHuge(p))
		return memory_failure_hugetlb(pfn, flags);
	if (TestSetPageHWPoison(p)) {
		pr_err("Memory failure: %#lx: already hardware poisoned\n",
			pfn);
		return 0;
	}

	orig_head = hpage = compound_head(p);
	num_poisoned_pages_inc();

	/*
	 * We need/can do nothing about count=0 pages.
	 * 1) it's a free page, and therefore in safe hand:
	 *    prep_new_page() will be the gate keeper.
	 * 2) it's part of a non-compound high order page.
	 *    Implies some kernel user: cannot stop them from
	 *    R/W the page; let's pray that the page has been
	 *    used and will be freed some time later.
	 * In fact it's dangerous to directly bump up page count from 0,
	 * that may make page_ref_freeze()/page_ref_unfreeze() mismatch.
	 */
	if (!(flags & MF_COUNT_INCREASED) && !get_hwpoison_page(p)) {
		if (is_free_buddy_page(p)) {
			action_result(pfn, MF_MSG_BUDDY, MF_DELAYED);
			return 0;
		} else {
			action_result(pfn, MF_MSG_KERNEL_HIGH_ORDER, MF_IGNORED);
			return -EBUSY;
		}
	}

	if (PageTransHuge(hpage)) {
		lock_page(p);
		if (!PageAnon(p) || unlikely(split_huge_page(p))) {
			unlock_page(p);
			if (!PageAnon(p))
				pr_err("Memory failure: %#lx: non anonymous thp\n",
					pfn);
			else
				pr_err("Memory failure: %#lx: thp split failed\n",
					pfn);
			if (TestClearPageHWPoison(p))
				num_poisoned_pages_dec();
			put_hwpoison_page(p);
			return -EBUSY;
		}
		unlock_page(p);
		VM_BUG_ON_PAGE(!page_count(p), p);
		hpage = compound_head(p);
	}

	/*
	 * We ignore non-LRU pages for good reasons.
	 * - PG_locked is only well defined for LRU pages and a few others
	 * - to avoid races with __SetPageLocked()
	 * - to avoid races with __SetPageSlab*() (and more non-atomic ops)
	 * The check (unnecessarily) ignores LRU pages being isolated and
	 * walked by the page reclaim code, however that's not a big loss.
	 */
	shake_page(p, 0);
	/* shake_page could have turned it free. */
	if (!PageLRU(p) && is_free_buddy_page(p)) {
		if (flags & MF_COUNT_INCREASED)
			action_result(pfn, MF_MSG_BUDDY, MF_DELAYED);
		else
			action_result(pfn, MF_MSG_BUDDY_2ND, MF_DELAYED);
		return 0;
	}

	lock_page(p);

	/*
	 * The page could have changed compound pages during the locking.
	 * If this happens just bail out.
	 */
	if (PageCompound(p) && compound_head(p) != orig_head) {
		action_result(pfn, MF_MSG_DIFFERENT_COMPOUND, MF_IGNORED);
		res = -EBUSY;
		goto out;
	}

	/*
	 * We use page flags to determine what action should be taken, but
	 * the flags can be modified by the error containment action.  One
	 * example is an mlocked page, where PG_mlocked is cleared by
	 * page_remove_rmap() in try_to_unmap_one(). So to determine page status
	 * correctly, we save a copy of the page flags at this time.
	 */
	if (PageHuge(p))
		page_flags = hpage->flags;
	else
		page_flags = p->flags;

	/*
	 * unpoison always clear PG_hwpoison inside page lock
	 */
	if (!PageHWPoison(p)) {
		pr_err("Memory failure: %#lx: just unpoisoned\n", pfn);
		num_poisoned_pages_dec();
		unlock_page(p);
		put_hwpoison_page(p);
		return 0;
	}
	if (hwpoison_filter(p)) {
		if (TestClearPageHWPoison(p))
			num_poisoned_pages_dec();
		unlock_page(p);
		put_hwpoison_page(p);
		return 0;
	}

	if (!PageTransTail(p) && !PageLRU(p))
		goto identify_page_state;

	/*
	 * It's very difficult to mess with pages currently under IO
	 * and in many cases impossible, so we just avoid it here.
	 */
	wait_on_page_writeback(p);

	/*
	 * Now take care of user space mappings.
	 * Abort on fail: __delete_from_page_cache() assumes unmapped page.
	 *
	 * When the raw error page is thp tail page, hpage points to the raw
	 * page after thp split.
	 */
	if (!hwpoison_user_mappings(p, pfn, flags, &hpage)) {
		action_result(pfn, MF_MSG_UNMAP_FAILED, MF_IGNORED);
		res = -EBUSY;
		goto out;
	}

	/*
	 * Torn down by someone else?
	 */
	if (PageLRU(p) && !PageSwapCache(p) && p->mapping == NULL) {
		action_result(pfn, MF_MSG_TRUNCATED_LRU, MF_IGNORED);
		res = -EBUSY;
		goto out;
	}

identify_page_state:
	res = identify_page_state(pfn, p, page_flags);
out:
	unlock_page(p);
	return res;
}