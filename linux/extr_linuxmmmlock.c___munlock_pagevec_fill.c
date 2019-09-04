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
struct zone {int dummy; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
struct pagevec {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PageTransCompound (struct page*) ; 
 int /*<<< orphan*/ * get_locked_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 unsigned long p4d_addr_end (unsigned long,unsigned long) ; 
 struct zone* page_zone (struct page*) ; 
 scalar_t__ pagevec_add (struct pagevec*,struct page*) ; 
 unsigned long pgd_addr_end (unsigned long,unsigned long) ; 
 unsigned long pmd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned long pud_addr_end (unsigned long,unsigned long) ; 
 struct page* vm_normal_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long __munlock_pagevec_fill(struct pagevec *pvec,
			struct vm_area_struct *vma, struct zone *zone,
			unsigned long start, unsigned long end)
{
	pte_t *pte;
	spinlock_t *ptl;

	/*
	 * Initialize pte walk starting at the already pinned page where we
	 * are sure that there is a pte, as it was pinned under the same
	 * mmap_sem write op.
	 */
	pte = get_locked_pte(vma->vm_mm, start,	&ptl);
	/* Make sure we do not cross the page table boundary */
	end = pgd_addr_end(start, end);
	end = p4d_addr_end(start, end);
	end = pud_addr_end(start, end);
	end = pmd_addr_end(start, end);

	/* The page next to the pinned page is the first we will try to get */
	start += PAGE_SIZE;
	while (start < end) {
		struct page *page = NULL;
		pte++;
		if (pte_present(*pte))
			page = vm_normal_page(vma, start, *pte);
		/*
		 * Break if page could not be obtained or the page's node+zone does not
		 * match
		 */
		if (!page || page_zone(page) != zone)
			break;

		/*
		 * Do not use pagevec for PTE-mapped THP,
		 * munlock_vma_pages_range() will handle them.
		 */
		if (PageTransCompound(page))
			break;

		get_page(page);
		/*
		 * Increase the address that will be returned *before* the
		 * eventual break due to pvec becoming full by adding the page
		 */
		start += PAGE_SIZE;
		if (pagevec_add(pvec, page) == 0)
			break;
	}
	pte_unmap_unlock(pte, ptl);
	return start;
}