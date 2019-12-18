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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ZSWAP_SWAPCACHE_EXIST ; 
 int ZSWAP_SWAPCACHE_FAIL ; 
 int ZSWAP_SWAPCACHE_NEW ; 
 struct page* __read_swap_cache_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int zswap_get_swap_cache_page(swp_entry_t entry,
				struct page **retpage)
{
	bool page_was_allocated;

	*retpage = __read_swap_cache_async(entry, GFP_KERNEL,
			NULL, 0, &page_was_allocated);
	if (page_was_allocated)
		return ZSWAP_SWAPCACHE_NEW;
	if (!*retpage)
		return ZSWAP_SWAPCACHE_FAIL;
	return ZSWAP_SWAPCACHE_EXIST;
}