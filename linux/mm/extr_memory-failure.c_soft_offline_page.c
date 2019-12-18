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
 int EIO ; 
 int MF_COUNT_INCREASED ; 
 scalar_t__ PageHWPoison (struct page*) ; 
 int get_any_page (struct page*,unsigned long,int) ; 
 int /*<<< orphan*/  get_online_mems () ; 
 scalar_t__ is_zone_device_page (struct page*) ; 
 unsigned long page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  pr_debug_ratelimited (char*,unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long) ; 
 int /*<<< orphan*/  put_hwpoison_page (struct page*) ; 
 int /*<<< orphan*/  put_online_mems () ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int soft_offline_free_page (struct page*) ; 
 int soft_offline_in_use_page (struct page*,int) ; 

int soft_offline_page(struct page *page, int flags)
{
	int ret;
	unsigned long pfn = page_to_pfn(page);

	if (is_zone_device_page(page)) {
		pr_debug_ratelimited("soft_offline: %#lx page is device page\n",
				pfn);
		if (flags & MF_COUNT_INCREASED)
			put_page(page);
		return -EIO;
	}

	if (PageHWPoison(page)) {
		pr_info("soft offline: %#lx page already poisoned\n", pfn);
		if (flags & MF_COUNT_INCREASED)
			put_hwpoison_page(page);
		return -EBUSY;
	}

	get_online_mems();
	ret = get_any_page(page, pfn, flags);
	put_online_mems();

	if (ret > 0)
		ret = soft_offline_in_use_page(page, flags);
	else if (ret == 0)
		ret = soft_offline_free_page(page);

	return ret;
}