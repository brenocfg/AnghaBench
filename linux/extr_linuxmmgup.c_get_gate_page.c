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
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 unsigned int FOLL_DUMP ; 
 unsigned int FOLL_WRITE ; 
 unsigned long TASK_SIZE ; 
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 struct vm_area_struct* get_gate_vma (struct mm_struct*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 scalar_t__ is_device_public_page (struct page*) ; 
 int /*<<< orphan*/  is_zero_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p4d_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset_gate (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/ * pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_trans_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 struct page* pte_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 struct page* vm_normal_page (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_gate_page(struct mm_struct *mm, unsigned long address,
		unsigned int gup_flags, struct vm_area_struct **vma,
		struct page **page)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	int ret = -EFAULT;

	/* user gate pages are read-only */
	if (gup_flags & FOLL_WRITE)
		return -EFAULT;
	if (address > TASK_SIZE)
		pgd = pgd_offset_k(address);
	else
		pgd = pgd_offset_gate(mm, address);
	BUG_ON(pgd_none(*pgd));
	p4d = p4d_offset(pgd, address);
	BUG_ON(p4d_none(*p4d));
	pud = pud_offset(p4d, address);
	BUG_ON(pud_none(*pud));
	pmd = pmd_offset(pud, address);
	if (!pmd_present(*pmd))
		return -EFAULT;
	VM_BUG_ON(pmd_trans_huge(*pmd));
	pte = pte_offset_map(pmd, address);
	if (pte_none(*pte))
		goto unmap;
	*vma = get_gate_vma(mm);
	if (!page)
		goto out;
	*page = vm_normal_page(*vma, address, *pte);
	if (!*page) {
		if ((gup_flags & FOLL_DUMP) || !is_zero_pfn(pte_pfn(*pte)))
			goto unmap;
		*page = pte_page(*pte);

		/*
		 * This should never happen (a device public page in the gate
		 * area).
		 */
		if (is_device_public_page(*page))
			goto unmap;
	}
	get_page(*page);
out:
	ret = 0;
unmap:
	pte_unmap(pte);
	return ret;
}