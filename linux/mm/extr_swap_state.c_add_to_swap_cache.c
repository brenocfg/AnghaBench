#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct page {int dummy; } ;
struct address_space {unsigned long nrpages; int /*<<< orphan*/  i_pages; } ;
typedef  scalar_t__ pgoff_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_15__ {scalar_t__ xa_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CACHE_INFO (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ClearPageSwapCache (struct page*) ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageSwapBacked (struct page*) ; 
 int PageSwapCache (struct page*) ; 
 int /*<<< orphan*/  SetPageSwapCache (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  XA_STATE_ORDER (TYPE_2__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mod_node_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  add_total ; 
 unsigned long compound_nr (struct page*) ; 
 int /*<<< orphan*/  compound_order (struct page*) ; 
 int /*<<< orphan*/  page_pgdat (struct page*) ; 
 int /*<<< orphan*/  page_ref_add (struct page*,unsigned long) ; 
 int /*<<< orphan*/  page_ref_sub (struct page*,unsigned long) ; 
 int /*<<< orphan*/  set_page_private (struct page*,scalar_t__) ; 
 struct address_space* swap_address_space (TYPE_1__) ; 
 scalar_t__ swp_offset (TYPE_1__) ; 
 TYPE_2__ xas ; 
 int /*<<< orphan*/  xas_create_range (TYPE_2__*) ; 
 int xas_error (TYPE_2__*) ; 
 int /*<<< orphan*/  xas_lock_irq (TYPE_2__*) ; 
 int /*<<< orphan*/  xas_next (TYPE_2__*) ; 
 scalar_t__ xas_nomem (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_store (TYPE_2__*,struct page*) ; 
 int /*<<< orphan*/  xas_unlock_irq (TYPE_2__*) ; 

int add_to_swap_cache(struct page *page, swp_entry_t entry, gfp_t gfp)
{
	struct address_space *address_space = swap_address_space(entry);
	pgoff_t idx = swp_offset(entry);
	XA_STATE_ORDER(xas, &address_space->i_pages, idx, compound_order(page));
	unsigned long i, nr = compound_nr(page);

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(PageSwapCache(page), page);
	VM_BUG_ON_PAGE(!PageSwapBacked(page), page);

	page_ref_add(page, nr);
	SetPageSwapCache(page);

	do {
		xas_lock_irq(&xas);
		xas_create_range(&xas);
		if (xas_error(&xas))
			goto unlock;
		for (i = 0; i < nr; i++) {
			VM_BUG_ON_PAGE(xas.xa_index != idx + i, page);
			set_page_private(page + i, entry.val + i);
			xas_store(&xas, page);
			xas_next(&xas);
		}
		address_space->nrpages += nr;
		__mod_node_page_state(page_pgdat(page), NR_FILE_PAGES, nr);
		ADD_CACHE_INFO(add_total, nr);
unlock:
		xas_unlock_irq(&xas);
	} while (xas_nomem(&xas, gfp));

	if (!xas_error(&xas))
		return 0;

	ClearPageSwapCache(page);
	page_ref_sub(page, nr);
	return xas_error(&xas);
}