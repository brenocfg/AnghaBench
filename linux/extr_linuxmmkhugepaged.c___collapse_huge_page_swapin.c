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
struct vm_fault {unsigned long address; int /*<<< orphan*/ * pte; struct vm_area_struct* vma; int /*<<< orphan*/  orig_pte; int /*<<< orphan*/  pgoff; int /*<<< orphan*/ * pmd; int /*<<< orphan*/  flags; } ;
struct vm_area_struct {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAULT_FLAG_ALLOW_RETRY ; 
 int HPAGE_PMD_NR ; 
 int PAGE_SIZE ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_RETRY ; 
 int do_swap_page (struct vm_fault*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ hugepage_vma_revalidate (struct mm_struct*,unsigned long,struct vm_area_struct**) ; 
 int /*<<< orphan*/  is_swap_pte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linear_page_index (struct vm_area_struct*,unsigned long) ; 
 int /*<<< orphan*/ * mm_find_pmd (struct mm_struct*,unsigned long) ; 
 void* pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_mm_collapse_huge_page_swapin (struct mm_struct*,int,int,int) ; 

__attribute__((used)) static bool __collapse_huge_page_swapin(struct mm_struct *mm,
					struct vm_area_struct *vma,
					unsigned long address, pmd_t *pmd,
					int referenced)
{
	int swapped_in = 0;
	vm_fault_t ret = 0;
	struct vm_fault vmf = {
		.vma = vma,
		.address = address,
		.flags = FAULT_FLAG_ALLOW_RETRY,
		.pmd = pmd,
		.pgoff = linear_page_index(vma, address),
	};

	/* we only decide to swapin, if there is enough young ptes */
	if (referenced < HPAGE_PMD_NR/2) {
		trace_mm_collapse_huge_page_swapin(mm, swapped_in, referenced, 0);
		return false;
	}
	vmf.pte = pte_offset_map(pmd, address);
	for (; vmf.address < address + HPAGE_PMD_NR*PAGE_SIZE;
			vmf.pte++, vmf.address += PAGE_SIZE) {
		vmf.orig_pte = *vmf.pte;
		if (!is_swap_pte(vmf.orig_pte))
			continue;
		swapped_in++;
		ret = do_swap_page(&vmf);

		/* do_swap_page returns VM_FAULT_RETRY with released mmap_sem */
		if (ret & VM_FAULT_RETRY) {
			down_read(&mm->mmap_sem);
			if (hugepage_vma_revalidate(mm, address, &vmf.vma)) {
				/* vma is no longer available, don't continue to swapin */
				trace_mm_collapse_huge_page_swapin(mm, swapped_in, referenced, 0);
				return false;
			}
			/* check if the pmd is still valid */
			if (mm_find_pmd(mm, address) != pmd) {
				trace_mm_collapse_huge_page_swapin(mm, swapped_in, referenced, 0);
				return false;
			}
		}
		if (ret & VM_FAULT_ERROR) {
			trace_mm_collapse_huge_page_swapin(mm, swapped_in, referenced, 0);
			return false;
		}
		/* pte is unmapped now, we need to map it */
		vmf.pte = pte_offset_map(pmd, vmf.address);
	}
	vmf.pte--;
	pte_unmap(vmf.pte);
	trace_mm_collapse_huge_page_swapin(mm, swapped_in, referenced, 1);
	return true;
}