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
typedef  unsigned long u64 ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENXIO ; 
 int EPERM ; 
 int /*<<< orphan*/  MF_COUNT_INCREASED ; 
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 int /*<<< orphan*/  PageLRU (struct page*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  get_hwpoison_page (struct page*) ; 
 int hwpoison_filter (struct page*) ; 
 int /*<<< orphan*/  hwpoison_filter_enable ; 
 int memory_failure (unsigned long,int /*<<< orphan*/ ) ; 
 struct page* pfn_to_page (unsigned long) ; 
 int /*<<< orphan*/  pfn_valid (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long) ; 
 int /*<<< orphan*/  put_hwpoison_page (struct page*) ; 
 int /*<<< orphan*/  shake_page (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hwpoison_inject(void *data, u64 val)
{
	unsigned long pfn = val;
	struct page *p;
	struct page *hpage;
	int err;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	if (!pfn_valid(pfn))
		return -ENXIO;

	p = pfn_to_page(pfn);
	hpage = compound_head(p);
	/*
	 * This implies unable to support free buddy pages.
	 */
	if (!get_hwpoison_page(p))
		return 0;

	if (!hwpoison_filter_enable)
		goto inject;

	shake_page(hpage, 0);
	/*
	 * This implies unable to support non-LRU pages.
	 */
	if (!PageLRU(hpage) && !PageHuge(p))
		goto put_out;

	/*
	 * do a racy check with elevated page count, to make sure PG_hwpoison
	 * will only be set for the targeted owner (or on a free page).
	 * memory_failure() will redo the check reliably inside page lock.
	 */
	err = hwpoison_filter(hpage);
	if (err)
		goto put_out;

inject:
	pr_info("Injecting memory failure at pfn %#lx\n", pfn);
	return memory_failure(pfn, MF_COUNT_INCREASED);
put_out:
	put_hwpoison_page(p);
	return 0;
}