#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {int /*<<< orphan*/  address; int /*<<< orphan*/  pmd; TYPE_2__* vma; } ;
typedef  int /*<<< orphan*/  pmd_t ;
struct TYPE_6__ {int vm_flags; TYPE_1__* vm_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* huge_fault ) (struct vm_fault*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PE_SIZE_PMD ; 
 int /*<<< orphan*/  VM_BUG_ON_VMA (int,TYPE_2__*) ; 
 int /*<<< orphan*/  VM_FAULT_FALLBACK ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  __split_huge_pmd (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_huge_pmd_wp_page (struct vm_fault*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct vm_fault*,int /*<<< orphan*/ ) ; 
 scalar_t__ vma_is_anonymous (TYPE_2__*) ; 

__attribute__((used)) static inline vm_fault_t wp_huge_pmd(struct vm_fault *vmf, pmd_t orig_pmd)
{
	if (vma_is_anonymous(vmf->vma))
		return do_huge_pmd_wp_page(vmf, orig_pmd);
	if (vmf->vma->vm_ops->huge_fault)
		return vmf->vma->vm_ops->huge_fault(vmf, PE_SIZE_PMD);

	/* COW handled on pte level: split pmd */
	VM_BUG_ON_VMA(vmf->vma->vm_flags & VM_SHARED, vmf->vma);
	__split_huge_pmd(vmf->vma, vmf->pmd, vmf->address, false, NULL);

	return VM_FAULT_FALLBACK;
}