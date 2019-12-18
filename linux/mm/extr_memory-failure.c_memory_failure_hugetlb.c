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
struct page {unsigned long flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int MF_COUNT_INCREASED ; 
 int /*<<< orphan*/  MF_DELAYED ; 
 int /*<<< orphan*/  MF_IGNORED ; 
 int /*<<< orphan*/  MF_MSG_FREE_HUGE ; 
 int /*<<< orphan*/  MF_MSG_NON_PMD_HUGE ; 
 int /*<<< orphan*/  MF_MSG_UNMAP_FAILED ; 
 scalar_t__ PMD_SIZE ; 
 scalar_t__ PageHWPoison (struct page*) ; 
 scalar_t__ TestClearPageHWPoison (struct page*) ; 
 scalar_t__ TestSetPageHWPoison (struct page*) ; 
 int /*<<< orphan*/  action_result (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  dissolve_free_huge_page (struct page*) ; 
 int /*<<< orphan*/  get_hwpoison_page (struct page*) ; 
 scalar_t__ huge_page_size (int /*<<< orphan*/ ) ; 
 scalar_t__ hwpoison_filter (struct page*) ; 
 int /*<<< orphan*/  hwpoison_user_mappings (struct page*,unsigned long,int,struct page**) ; 
 int identify_page_state (unsigned long,struct page*,unsigned long) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int /*<<< orphan*/  num_poisoned_pages_dec () ; 
 int /*<<< orphan*/  num_poisoned_pages_inc () ; 
 int /*<<< orphan*/  page_hstate (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long) ; 
 int /*<<< orphan*/  put_hwpoison_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int memory_failure_hugetlb(unsigned long pfn, int flags)
{
	struct page *p = pfn_to_page(pfn);
	struct page *head = compound_head(p);
	int res;
	unsigned long page_flags;

	if (TestSetPageHWPoison(head)) {
		pr_err("Memory failure: %#lx: already hardware poisoned\n",
		       pfn);
		return 0;
	}

	num_poisoned_pages_inc();

	if (!(flags & MF_COUNT_INCREASED) && !get_hwpoison_page(p)) {
		/*
		 * Check "filter hit" and "race with other subpage."
		 */
		lock_page(head);
		if (PageHWPoison(head)) {
			if ((hwpoison_filter(p) && TestClearPageHWPoison(p))
			    || (p != head && TestSetPageHWPoison(head))) {
				num_poisoned_pages_dec();
				unlock_page(head);
				return 0;
			}
		}
		unlock_page(head);
		dissolve_free_huge_page(p);
		action_result(pfn, MF_MSG_FREE_HUGE, MF_DELAYED);
		return 0;
	}

	lock_page(head);
	page_flags = head->flags;

	if (!PageHWPoison(head)) {
		pr_err("Memory failure: %#lx: just unpoisoned\n", pfn);
		num_poisoned_pages_dec();
		unlock_page(head);
		put_hwpoison_page(head);
		return 0;
	}

	/*
	 * TODO: hwpoison for pud-sized hugetlb doesn't work right now, so
	 * simply disable it. In order to make it work properly, we need
	 * make sure that:
	 *  - conversion of a pud that maps an error hugetlb into hwpoison
	 *    entry properly works, and
	 *  - other mm code walking over page table is aware of pud-aligned
	 *    hwpoison entries.
	 */
	if (huge_page_size(page_hstate(head)) > PMD_SIZE) {
		action_result(pfn, MF_MSG_NON_PMD_HUGE, MF_IGNORED);
		res = -EBUSY;
		goto out;
	}

	if (!hwpoison_user_mappings(p, pfn, flags, &head)) {
		action_result(pfn, MF_MSG_UNMAP_FAILED, MF_IGNORED);
		res = -EBUSY;
		goto out;
	}

	res = identify_page_state(pfn, p, page_flags);
out:
	unlock_page(head);
	return res;
}