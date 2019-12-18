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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; } ;
struct page {int /*<<< orphan*/  _mapcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  NR_ANON_MAPPED ; 
 int /*<<< orphan*/  NR_ANON_THPS ; 
 int PageTransCompound (struct page*) ; 
 int /*<<< orphan*/  PageTransHuge (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_VMA (int,struct vm_area_struct*) ; 
 int /*<<< orphan*/  __SetPageSwapBacked (struct page*) ; 
 int /*<<< orphan*/  __inc_node_page_state (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mod_node_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __page_set_anon_rmap (struct page*,struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * compound_mapcount_ptr (struct page*) ; 
 int hpage_nr_pages (struct page*) ; 
 int /*<<< orphan*/  page_pgdat (struct page*) ; 

void page_add_new_anon_rmap(struct page *page,
	struct vm_area_struct *vma, unsigned long address, bool compound)
{
	int nr = compound ? hpage_nr_pages(page) : 1;

	VM_BUG_ON_VMA(address < vma->vm_start || address >= vma->vm_end, vma);
	__SetPageSwapBacked(page);
	if (compound) {
		VM_BUG_ON_PAGE(!PageTransHuge(page), page);
		/* increment count (starts at -1) */
		atomic_set(compound_mapcount_ptr(page), 0);
		__inc_node_page_state(page, NR_ANON_THPS);
	} else {
		/* Anon THP always mapped first with PMD */
		VM_BUG_ON_PAGE(PageTransCompound(page), page);
		/* increment count (starts at -1) */
		atomic_set(&page->_mapcount, 0);
	}
	__mod_node_page_state(page_pgdat(page), NR_ANON_MAPPED, nr);
	__page_set_anon_rmap(page, vma, address, 1);
}