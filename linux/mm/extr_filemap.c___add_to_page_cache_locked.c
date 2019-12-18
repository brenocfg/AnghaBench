#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {struct address_space* mapping; int /*<<< orphan*/  index; } ;
struct mem_cgroup {int dummy; } ;
struct address_space {int /*<<< orphan*/  nrpages; int /*<<< orphan*/  nrexceptional; int /*<<< orphan*/  i_pages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int GFP_RECLAIM_MASK ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int PageHuge (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int PageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  XA_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __inc_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  mapping_set_update (int /*<<< orphan*/ *,struct address_space*) ; 
 int /*<<< orphan*/  mem_cgroup_cancel_charge (struct page*,struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  mem_cgroup_commit_charge (struct page*,struct mem_cgroup*,int,int) ; 
 int mem_cgroup_try_charge (struct page*,int /*<<< orphan*/ ,int,struct mem_cgroup**,int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  trace_mm_filemap_add_to_page_cache (struct page*) ; 
 scalar_t__ xa_is_value (void*) ; 
 int /*<<< orphan*/  xas ; 
 int xas_error (int /*<<< orphan*/ *) ; 
 void* xas_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xas_lock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ xas_nomem (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xas_set_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xas_store (int /*<<< orphan*/ *,struct page*) ; 
 int /*<<< orphan*/  xas_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __add_to_page_cache_locked(struct page *page,
				      struct address_space *mapping,
				      pgoff_t offset, gfp_t gfp_mask,
				      void **shadowp)
{
	XA_STATE(xas, &mapping->i_pages, offset);
	int huge = PageHuge(page);
	struct mem_cgroup *memcg;
	int error;
	void *old;

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(PageSwapBacked(page), page);
	mapping_set_update(&xas, mapping);

	if (!huge) {
		error = mem_cgroup_try_charge(page, current->mm,
					      gfp_mask, &memcg, false);
		if (error)
			return error;
	}

	get_page(page);
	page->mapping = mapping;
	page->index = offset;

	do {
		xas_lock_irq(&xas);
		old = xas_load(&xas);
		if (old && !xa_is_value(old))
			xas_set_err(&xas, -EEXIST);
		xas_store(&xas, page);
		if (xas_error(&xas))
			goto unlock;

		if (xa_is_value(old)) {
			mapping->nrexceptional--;
			if (shadowp)
				*shadowp = old;
		}
		mapping->nrpages++;

		/* hugetlb pages do not participate in page cache accounting */
		if (!huge)
			__inc_node_page_state(page, NR_FILE_PAGES);
unlock:
		xas_unlock_irq(&xas);
	} while (xas_nomem(&xas, gfp_mask & GFP_RECLAIM_MASK));

	if (xas_error(&xas))
		goto error;

	if (!huge)
		mem_cgroup_commit_charge(page, memcg, false, false);
	trace_mm_filemap_add_to_page_cache(page);
	return 0;
error:
	page->mapping = NULL;
	/* Leave page->index set: truncation relies upon it */
	if (!huge)
		mem_cgroup_cancel_charge(page, memcg, false);
	put_page(page);
	return xas_error(&xas);
}