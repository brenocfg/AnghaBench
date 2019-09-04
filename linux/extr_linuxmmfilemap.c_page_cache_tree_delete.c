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
struct radix_tree_node {int dummy; } ;
struct page {int /*<<< orphan*/ * mapping; scalar_t__ index; } ;
struct address_space {int nrexceptional; int nrpages; int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 scalar_t__ PageHuge (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int PageTail (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  __radix_tree_lookup (int /*<<< orphan*/ *,scalar_t__,struct radix_tree_node**,void***) ; 
 int /*<<< orphan*/  __radix_tree_replace (int /*<<< orphan*/ *,struct radix_tree_node*,void**,void*,int /*<<< orphan*/ ) ; 
 int hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  radix_tree_clear_tags (int /*<<< orphan*/ *,struct radix_tree_node*,void**) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  workingset_lookup_update (struct address_space*) ; 

__attribute__((used)) static void page_cache_tree_delete(struct address_space *mapping,
				   struct page *page, void *shadow)
{
	int i, nr;

	/* hugetlb pages are represented by one entry in the radix tree */
	nr = PageHuge(page) ? 1 : hpage_nr_pages(page);

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(PageTail(page), page);
	VM_BUG_ON_PAGE(nr != 1 && shadow, page);

	for (i = 0; i < nr; i++) {
		struct radix_tree_node *node;
		void **slot;

		__radix_tree_lookup(&mapping->i_pages, page->index + i,
				    &node, &slot);

		VM_BUG_ON_PAGE(!node && nr != 1, page);

		radix_tree_clear_tags(&mapping->i_pages, node, slot);
		__radix_tree_replace(&mapping->i_pages, node, slot, shadow,
				workingset_lookup_update(mapping));
	}

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