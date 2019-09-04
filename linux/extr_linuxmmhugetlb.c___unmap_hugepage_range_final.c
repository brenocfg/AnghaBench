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
struct vm_area_struct {int /*<<< orphan*/  vm_flags; } ;
struct page {int dummy; } ;
struct mmu_gather {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MAYSHARE ; 
 int /*<<< orphan*/  __unmap_hugepage_range (struct mmu_gather*,struct vm_area_struct*,unsigned long,unsigned long,struct page*) ; 

void __unmap_hugepage_range_final(struct mmu_gather *tlb,
			  struct vm_area_struct *vma, unsigned long start,
			  unsigned long end, struct page *ref_page)
{
	__unmap_hugepage_range(tlb, vma, start, end, ref_page);

	/*
	 * Clear this flag so that x86's huge_pmd_share page_table_shareable
	 * test will fail on a vma being torn down, and not grab a page table
	 * on its way out.  We're lucky that the flag has such an appropriate
	 * name, and can in fact be safely cleared here. We could clear it
	 * before the __unmap_hugepage_range above, but all that's necessary
	 * is to clear it before releasing the i_mmap_rwsem. This works
	 * because in the context this is called, the VMA is about to be
	 * destroyed and the i_mmap_rwsem is held.
	 */
	vma->vm_flags &= ~VM_MAYSHARE;
}