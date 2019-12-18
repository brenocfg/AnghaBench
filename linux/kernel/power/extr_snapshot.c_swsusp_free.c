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
 unsigned long BM_END_OF_MAP ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 scalar_t__ alloc_highmem ; 
 scalar_t__ alloc_normal ; 
 int /*<<< orphan*/ * buffer ; 
 int /*<<< orphan*/  forbidden_pages_map ; 
 int /*<<< orphan*/  free_pages_map ; 
 int /*<<< orphan*/  hibernate_restore_protection_end () ; 
 int /*<<< orphan*/  hibernate_restore_unprotect_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_bm_clear_current (int /*<<< orphan*/ ) ; 
 unsigned long memory_bm_next_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_bm_position_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ nr_copy_pages ; 
 scalar_t__ nr_meta_pages ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 struct page* pfn_to_page (unsigned long) ; 
 scalar_t__ pfn_valid (unsigned long) ; 
 int /*<<< orphan*/ * restore_pblist ; 

void swsusp_free(void)
{
	unsigned long fb_pfn, fr_pfn;

	if (!forbidden_pages_map || !free_pages_map)
		goto out;

	memory_bm_position_reset(forbidden_pages_map);
	memory_bm_position_reset(free_pages_map);

loop:
	fr_pfn = memory_bm_next_pfn(free_pages_map);
	fb_pfn = memory_bm_next_pfn(forbidden_pages_map);

	/*
	 * Find the next bit set in both bitmaps. This is guaranteed to
	 * terminate when fb_pfn == fr_pfn == BM_END_OF_MAP.
	 */
	do {
		if (fb_pfn < fr_pfn)
			fb_pfn = memory_bm_next_pfn(forbidden_pages_map);
		if (fr_pfn < fb_pfn)
			fr_pfn = memory_bm_next_pfn(free_pages_map);
	} while (fb_pfn != fr_pfn);

	if (fr_pfn != BM_END_OF_MAP && pfn_valid(fr_pfn)) {
		struct page *page = pfn_to_page(fr_pfn);

		memory_bm_clear_current(forbidden_pages_map);
		memory_bm_clear_current(free_pages_map);
		hibernate_restore_unprotect_page(page_address(page));
		__free_page(page);
		goto loop;
	}

out:
	nr_copy_pages = 0;
	nr_meta_pages = 0;
	restore_pblist = NULL;
	buffer = NULL;
	alloc_normal = 0;
	alloc_highmem = 0;
	hibernate_restore_protection_end();
}