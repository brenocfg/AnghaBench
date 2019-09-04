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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct address_space {int dummy; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  __ClearPageLocked (struct page*) ; 
 int /*<<< orphan*/  __SetPageLocked (struct page*) ; 
 int /*<<< orphan*/  __SetPageSwapBacked (struct page*) ; 
 int __add_to_swap_cache (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __swp_swapcount (int /*<<< orphan*/ ) ; 
 struct page* alloc_page_vma (int,struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/  cond_resched () ; 
 struct page* find_get_page (struct address_space*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  lru_cache_add_anon (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  put_swap_page (struct page*,int /*<<< orphan*/ ) ; 
 int radix_tree_maybe_preload (int) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 struct address_space* swap_address_space (int /*<<< orphan*/ ) ; 
 scalar_t__ swap_slot_cache_enabled ; 
 int swapcache_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swp_offset (int /*<<< orphan*/ ) ; 

struct page *__read_swap_cache_async(swp_entry_t entry, gfp_t gfp_mask,
			struct vm_area_struct *vma, unsigned long addr,
			bool *new_page_allocated)
{
	struct page *found_page, *new_page = NULL;
	struct address_space *swapper_space = swap_address_space(entry);
	int err;
	*new_page_allocated = false;

	do {
		/*
		 * First check the swap cache.  Since this is normally
		 * called after lookup_swap_cache() failed, re-calling
		 * that would confuse statistics.
		 */
		found_page = find_get_page(swapper_space, swp_offset(entry));
		if (found_page)
			break;

		/*
		 * Just skip read ahead for unused swap slot.
		 * During swap_off when swap_slot_cache is disabled,
		 * we have to handle the race between putting
		 * swap entry in swap cache and marking swap slot
		 * as SWAP_HAS_CACHE.  That's done in later part of code or
		 * else swap_off will be aborted if we return NULL.
		 */
		if (!__swp_swapcount(entry) && swap_slot_cache_enabled)
			break;

		/*
		 * Get a new page to read into from swap.
		 */
		if (!new_page) {
			new_page = alloc_page_vma(gfp_mask, vma, addr);
			if (!new_page)
				break;		/* Out of memory */
		}

		/*
		 * call radix_tree_preload() while we can wait.
		 */
		err = radix_tree_maybe_preload(gfp_mask & GFP_KERNEL);
		if (err)
			break;

		/*
		 * Swap entry may have been freed since our caller observed it.
		 */
		err = swapcache_prepare(entry);
		if (err == -EEXIST) {
			radix_tree_preload_end();
			/*
			 * We might race against get_swap_page() and stumble
			 * across a SWAP_HAS_CACHE swap_map entry whose page
			 * has not been brought into the swapcache yet.
			 */
			cond_resched();
			continue;
		}
		if (err) {		/* swp entry is obsolete ? */
			radix_tree_preload_end();
			break;
		}

		/* May fail (-ENOMEM) if radix-tree node allocation failed. */
		__SetPageLocked(new_page);
		__SetPageSwapBacked(new_page);
		err = __add_to_swap_cache(new_page, entry);
		if (likely(!err)) {
			radix_tree_preload_end();
			/*
			 * Initiate read into locked page and return.
			 */
			lru_cache_add_anon(new_page);
			*new_page_allocated = true;
			return new_page;
		}
		radix_tree_preload_end();
		__ClearPageLocked(new_page);
		/*
		 * add_to_swap_cache() doesn't return -EEXIST, so we can safely
		 * clear SWAP_HAS_CACHE flag.
		 */
		put_swap_page(new_page, entry);
	} while (err != -ENOMEM);

	if (new_page)
		put_page(new_page);
	return found_page;
}