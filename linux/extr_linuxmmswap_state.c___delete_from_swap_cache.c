#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct page {int dummy; } ;
struct address_space {int nrpages; int /*<<< orphan*/  i_pages; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CACHE_INFO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ClearPageSwapCache (struct page*) ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageSwapCache (struct page*) ; 
 int PageWriteback (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  __mod_node_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_total ; 
 int hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  page_pgdat (struct page*) ; 
 int /*<<< orphan*/  page_private (struct page*) ; 
 int /*<<< orphan*/  radix_tree_delete (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 struct address_space* swap_address_space (TYPE_1__) ; 
 scalar_t__ swp_offset (TYPE_1__) ; 

void __delete_from_swap_cache(struct page *page)
{
	struct address_space *address_space;
	int i, nr = hpage_nr_pages(page);
	swp_entry_t entry;
	pgoff_t idx;

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(!PageSwapCache(page), page);
	VM_BUG_ON_PAGE(PageWriteback(page), page);

	entry.val = page_private(page);
	address_space = swap_address_space(entry);
	idx = swp_offset(entry);
	for (i = 0; i < nr; i++) {
		radix_tree_delete(&address_space->i_pages, idx + i);
		set_page_private(page + i, 0);
	}
	ClearPageSwapCache(page);
	address_space->nrpages -= nr;
	__mod_node_page_state(page_pgdat(page), NR_FILE_PAGES, -nr);
	ADD_CACHE_INFO(del_total, nr);
}