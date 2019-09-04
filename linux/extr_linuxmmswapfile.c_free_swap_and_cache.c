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
struct swap_info_struct {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  PageWriteback (struct page*) ; 
 unsigned char SWAP_HAS_CACHE ; 
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 unsigned char __swap_entry_free (struct swap_info_struct*,int /*<<< orphan*/ ,int) ; 
 struct swap_info_struct* _swap_info_get (int /*<<< orphan*/ ) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/  delete_from_swap_cache (struct page*) ; 
 struct page* find_get_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_swap_slot (int /*<<< orphan*/ ) ; 
 scalar_t__ mem_cgroup_swap_full (struct page*) ; 
 scalar_t__ non_swap_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_mapped (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  swap_address_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_page_trans_huge_swapped (struct swap_info_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swp_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int free_swap_and_cache(swp_entry_t entry)
{
	struct swap_info_struct *p;
	struct page *page = NULL;
	unsigned char count;

	if (non_swap_entry(entry))
		return 1;

	p = _swap_info_get(entry);
	if (p) {
		count = __swap_entry_free(p, entry, 1);
		if (count == SWAP_HAS_CACHE &&
		    !swap_page_trans_huge_swapped(p, entry)) {
			page = find_get_page(swap_address_space(entry),
					     swp_offset(entry));
			if (page && !trylock_page(page)) {
				put_page(page);
				page = NULL;
			}
		} else if (!count)
			free_swap_slot(entry);
	}
	if (page) {
		/*
		 * Not mapped elsewhere, or swap space full? Free it!
		 * Also recheck PageSwapCache now page is locked (above).
		 */
		if (PageSwapCache(page) && !PageWriteback(page) &&
		    (!page_mapped(page) || mem_cgroup_swap_full(page)) &&
		    !swap_page_trans_huge_swapped(p, entry)) {
			page = compound_head(page);
			delete_from_swap_cache(page);
			SetPageDirty(page);
		}
		unlock_page(page);
		put_page(page);
	}
	return p != NULL;
}