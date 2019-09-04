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
struct vm_area_struct {int vm_flags; struct mm_struct* vm_mm; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int /*<<< orphan*/  PUD_SHIFT ; 
 int VM_HUGETLB ; 
 int /*<<< orphan*/  __hugepd (int /*<<< orphan*/ ) ; 
 struct page* follow_devmap_pud (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 struct page* follow_huge_pd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct page* follow_huge_pud (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int) ; 
 struct page* follow_pmd_mask (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int,unsigned int*) ; 
 scalar_t__ is_hugepd (int /*<<< orphan*/ ) ; 
 struct page* no_page_table (struct vm_area_struct*,unsigned int) ; 
 int /*<<< orphan*/  pud_bad (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_devmap (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_huge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_lock (struct mm_struct*,int /*<<< orphan*/ *) ; 
 scalar_t__ pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *follow_pud_mask(struct vm_area_struct *vma,
				    unsigned long address, p4d_t *p4dp,
				    unsigned int flags, unsigned int *page_mask)
{
	pud_t *pud;
	spinlock_t *ptl;
	struct page *page;
	struct mm_struct *mm = vma->vm_mm;

	pud = pud_offset(p4dp, address);
	if (pud_none(*pud))
		return no_page_table(vma, flags);
	if (pud_huge(*pud) && vma->vm_flags & VM_HUGETLB) {
		page = follow_huge_pud(mm, address, pud, flags);
		if (page)
			return page;
		return no_page_table(vma, flags);
	}
	if (is_hugepd(__hugepd(pud_val(*pud)))) {
		page = follow_huge_pd(vma, address,
				      __hugepd(pud_val(*pud)), flags,
				      PUD_SHIFT);
		if (page)
			return page;
		return no_page_table(vma, flags);
	}
	if (pud_devmap(*pud)) {
		ptl = pud_lock(mm, pud);
		page = follow_devmap_pud(vma, address, pud, flags);
		spin_unlock(ptl);
		if (page)
			return page;
	}
	if (unlikely(pud_bad(*pud)))
		return no_page_table(vma, flags);

	return follow_pmd_mask(vma, address, pud, flags, page_mask);
}