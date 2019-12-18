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
typedef  int vm_fault_t ;
struct vm_fault {unsigned long address; int flags; int /*<<< orphan*/  ptl; int /*<<< orphan*/ * pmd; struct vm_area_struct* vma; } ;
struct vm_area_struct {int /*<<< orphan*/  vm_mm; int /*<<< orphan*/  vm_flags; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgtable_t ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int FAULT_FLAG_WRITE ; 
 unsigned long HPAGE_PMD_MASK ; 
 int /*<<< orphan*/  HPAGE_PMD_ORDER ; 
 int /*<<< orphan*/  THP_FAULT_FALLBACK ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int VM_FAULT_FALLBACK ; 
 int VM_FAULT_OOM ; 
 int /*<<< orphan*/  VM_UFFD_MISSING ; 
 int __do_huge_pmd_anonymous_page (struct vm_fault*,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_hugepage_direct_gfpmask (struct vm_area_struct*) ; 
 struct page* alloc_hugepage_vma (int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ) ; 
 int anon_vma_prepare (struct vm_area_struct*) ; 
 int check_stable_address_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int handle_userfault (struct vm_fault*,int /*<<< orphan*/ ) ; 
 int khugepaged_enter (struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_forbids_zeropage (int /*<<< orphan*/ ) ; 
 struct page* mm_get_huge_zero_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prep_transhuge_page (struct page*) ; 
 int /*<<< orphan*/  pte_alloc_one (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_huge_zero_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,struct page*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transhuge_vma_suitable (struct vm_area_struct*,unsigned long) ; 
 scalar_t__ transparent_hugepage_use_zero_page () ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ userfaultfd_missing (struct vm_area_struct*) ; 

vm_fault_t do_huge_pmd_anonymous_page(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	gfp_t gfp;
	struct page *page;
	unsigned long haddr = vmf->address & HPAGE_PMD_MASK;

	if (!transhuge_vma_suitable(vma, haddr))
		return VM_FAULT_FALLBACK;
	if (unlikely(anon_vma_prepare(vma)))
		return VM_FAULT_OOM;
	if (unlikely(khugepaged_enter(vma, vma->vm_flags)))
		return VM_FAULT_OOM;
	if (!(vmf->flags & FAULT_FLAG_WRITE) &&
			!mm_forbids_zeropage(vma->vm_mm) &&
			transparent_hugepage_use_zero_page()) {
		pgtable_t pgtable;
		struct page *zero_page;
		bool set;
		vm_fault_t ret;
		pgtable = pte_alloc_one(vma->vm_mm);
		if (unlikely(!pgtable))
			return VM_FAULT_OOM;
		zero_page = mm_get_huge_zero_page(vma->vm_mm);
		if (unlikely(!zero_page)) {
			pte_free(vma->vm_mm, pgtable);
			count_vm_event(THP_FAULT_FALLBACK);
			return VM_FAULT_FALLBACK;
		}
		vmf->ptl = pmd_lock(vma->vm_mm, vmf->pmd);
		ret = 0;
		set = false;
		if (pmd_none(*vmf->pmd)) {
			ret = check_stable_address_space(vma->vm_mm);
			if (ret) {
				spin_unlock(vmf->ptl);
			} else if (userfaultfd_missing(vma)) {
				spin_unlock(vmf->ptl);
				ret = handle_userfault(vmf, VM_UFFD_MISSING);
				VM_BUG_ON(ret & VM_FAULT_FALLBACK);
			} else {
				set_huge_zero_page(pgtable, vma->vm_mm, vma,
						   haddr, vmf->pmd, zero_page);
				spin_unlock(vmf->ptl);
				set = true;
			}
		} else
			spin_unlock(vmf->ptl);
		if (!set)
			pte_free(vma->vm_mm, pgtable);
		return ret;
	}
	gfp = alloc_hugepage_direct_gfpmask(vma);
	page = alloc_hugepage_vma(gfp, vma, haddr, HPAGE_PMD_ORDER);
	if (unlikely(!page)) {
		count_vm_event(THP_FAULT_FALLBACK);
		return VM_FAULT_FALLBACK;
	}
	prep_transhuge_page(page);
	return __do_huge_pmd_anonymous_page(vmf, page, gfp);
}