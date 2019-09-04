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
struct address_space {int /*<<< orphan*/  i_pages; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int GFP_RECLAIM_MASK ; 
 int /*<<< orphan*/  NR_FILE_PAGES ; 
 int PageHuge (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int PageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  __inc_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  mem_cgroup_cancel_charge (struct page*,struct mem_cgroup*,int) ; 
 int /*<<< orphan*/  mem_cgroup_commit_charge (struct page*,struct mem_cgroup*,int,int) ; 
 int mem_cgroup_try_charge (struct page*,int /*<<< orphan*/ ,int,struct mem_cgroup**,int) ; 
 int page_cache_tree_insert (struct address_space*,struct page*,void**) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int radix_tree_maybe_preload (int) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  trace_mm_filemap_add_to_page_cache (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __add_to_page_cache_locked(struct page *page,
				      struct address_space *mapping,
				      pgoff_t offset, gfp_t gfp_mask,
				      void **shadowp)
{
	int huge = PageHuge(page);
	struct mem_cgroup *memcg;
	int error;

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(PageSwapBacked(page), page);

	if (!huge) {
		error = mem_cgroup_try_charge(page, current->mm,
					      gfp_mask, &memcg, false);
		if (error)
			return error;
	}

	error = radix_tree_maybe_preload(gfp_mask & GFP_RECLAIM_MASK);
	if (error) {
		if (!huge)
			mem_cgroup_cancel_charge(page, memcg, false);
		return error;
	}

	get_page(page);
	page->mapping = mapping;
	page->index = offset;

	xa_lock_irq(&mapping->i_pages);
	error = page_cache_tree_insert(mapping, page, shadowp);
	radix_tree_preload_end();
	if (unlikely(error))
		goto err_insert;

	/* hugetlb pages do not participate in page cache accounting. */
	if (!huge)
		__inc_node_page_state(page, NR_FILE_PAGES);
	xa_unlock_irq(&mapping->i_pages);
	if (!huge)
		mem_cgroup_commit_charge(page, memcg, false, false);
	trace_mm_filemap_add_to_page_cache(page);
	return 0;
err_insert:
	page->mapping = NULL;
	/* Leave page->index set: truncation relies upon it */
	xa_unlock_irq(&mapping->i_pages);
	if (!huge)
		mem_cgroup_cancel_charge(page, memcg, false);
	put_page(page);
	return error;
}