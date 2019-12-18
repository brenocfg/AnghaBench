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
struct page {int /*<<< orphan*/ * mapping; int /*<<< orphan*/  index; } ;
struct address_space {unsigned int nrexceptional; unsigned int nrpages; int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int PageTail (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  XA_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int compound_nr (struct page*) ; 
 int /*<<< orphan*/  compound_order (struct page*) ; 
 int /*<<< orphan*/  mapping_set_update (int /*<<< orphan*/ *,struct address_space*) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  xas ; 
 int /*<<< orphan*/  xas_init_marks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_set_order (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_store (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void page_cache_delete(struct address_space *mapping,
				   struct page *page, void *shadow)
{
	XA_STATE(xas, &mapping->i_pages, page->index);
	unsigned int nr = 1;

	mapping_set_update(&xas, mapping);

	/* hugetlb pages are represented by a single entry in the xarray */
	if (!PageHuge(page)) {
		xas_set_order(&xas, page->index, compound_order(page));
		nr = compound_nr(page);
	}

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(PageTail(page), page);
	VM_BUG_ON_PAGE(nr != 1 && shadow, page);

	xas_store(&xas, shadow);
	xas_init_marks(&xas);

	page->mapping = NULL;
	/* Leave page->index set: truncation lookup relies upon it */

	if (shadow) {
		mapping->nrexceptional += nr;
		/*
		 * Make sure the nrexceptional update is committed before
		 * the nrpages update so that final truncate racing
		 * with reclaim does not see both counters 0 at the
		 * same time and miss a shadow entry.
		 */
		smp_wmb();
	}
	mapping->nrpages -= nr;
}