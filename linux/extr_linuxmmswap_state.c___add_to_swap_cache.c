#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct page {int dummy; } ;
struct address_space {int nrpages; int /*<<< orphan*/  i_pages; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CACHE_INFO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ClearPageSwapCache (struct page*) ; 
 int EEXIST ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageSwapBacked (struct page*) ; 
 int PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  SetPageSwapCache (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  __mod_node_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_total ; 
 int hpage_nr_pages (struct page*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  page_pgdat (struct page*) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,int) ; 
 int /*<<< orphan*/  page_ref_sub (struct page*,int) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,scalar_t__) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,scalar_t__,struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 struct address_space* swap_address_space (TYPE_1__) ; 
 scalar_t__ swp_offset (TYPE_1__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

int __add_to_swap_cache(struct page *page, swp_entry_t entry)
{
	int error, i, nr = hpage_nr_pages(page);
	struct address_space *address_space;
	pgoff_t idx = swp_offset(entry);

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(PageSwapCache(page), page);
	VM_BUG_ON_PAGE(!PageSwapBacked(page), page);

	page_ref_add(page, nr);
	SetPageSwapCache(page);

	address_space = swap_address_space(entry);
	xa_lock_irq(&address_space->i_pages);
	for (i = 0; i < nr; i++) {
		set_page_private(page + i, entry.val + i);
		error = radix_tree_insert(&address_space->i_pages,
					  idx + i, page + i);
		if (unlikely(error))
			break;
	}
	if (likely(!error)) {
		address_space->nrpages += nr;
		__mod_node_page_state(page_pgdat(page), NR_FILE_PAGES, nr);
		ADD_CACHE_INFO(add_total, nr);
	} else {
		/*
		 * Only the context which have set SWAP_HAS_CACHE flag
		 * would call add_to_swap_cache().
		 * So add_to_swap_cache() doesn't returns -EEXIST.
		 */
		VM_BUG_ON(error == -EEXIST);
		set_page_private(page + i, 0UL);
		while (i--) {
			radix_tree_delete(&address_space->i_pages, idx + i);
			set_page_private(page + i, 0UL);
		}
		ClearPageSwapCache(page);
		page_ref_sub(page, nr);
	}
	xa_unlock_irq(&address_space->i_pages);

	return error;
}