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
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_area_struct {int vm_flags; unsigned long vm_start; unsigned long vm_end; } ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PFN_DEV ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int VM_MIXEDMAP ; 
 int VM_PFNMAP ; 
 int /*<<< orphan*/  __pfn_to_pfn_t (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_pfn (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_cow_mapping (int) ; 
 int /*<<< orphan*/  pfn_modify_allowed (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ pfn_valid (unsigned long) ; 
 int /*<<< orphan*/  track_pfn_insert (struct vm_area_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

vm_fault_t vmf_insert_pfn_prot(struct vm_area_struct *vma, unsigned long addr,
			unsigned long pfn, pgprot_t pgprot)
{
	/*
	 * Technically, architectures with pte_special can avoid all these
	 * restrictions (same for remap_pfn_range).  However we would like
	 * consistency in testing and feature parity among all, so we should
	 * try to keep these invariants in place for everybody.
	 */
	BUG_ON(!(vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP)));
	BUG_ON((vma->vm_flags & (VM_PFNMAP|VM_MIXEDMAP)) ==
						(VM_PFNMAP|VM_MIXEDMAP));
	BUG_ON((vma->vm_flags & VM_PFNMAP) && is_cow_mapping(vma->vm_flags));
	BUG_ON((vma->vm_flags & VM_MIXEDMAP) && pfn_valid(pfn));

	if (addr < vma->vm_start || addr >= vma->vm_end)
		return VM_FAULT_SIGBUS;

	if (!pfn_modify_allowed(pfn, pgprot))
		return VM_FAULT_SIGBUS;

	track_pfn_insert(vma, &pgprot, __pfn_to_pfn_t(pfn, PFN_DEV));

	return insert_pfn(vma, addr, __pfn_to_pfn_t(pfn, PFN_DEV), pgprot,
			false);
}