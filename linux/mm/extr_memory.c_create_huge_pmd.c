#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {TYPE_2__* vma; } ;
struct TYPE_4__ {TYPE_1__* vm_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* huge_fault ) (struct vm_fault*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PE_SIZE_PMD ; 
 int /*<<< orphan*/  VM_FAULT_FALLBACK ; 
 int /*<<< orphan*/  do_huge_pmd_anonymous_page (struct vm_fault*) ; 
 int /*<<< orphan*/  stub1 (struct vm_fault*,int /*<<< orphan*/ ) ; 
 scalar_t__ vma_is_anonymous (TYPE_2__*) ; 

__attribute__((used)) static inline vm_fault_t create_huge_pmd(struct vm_fault *vmf)
{
	if (vma_is_anonymous(vmf->vma))
		return do_huge_pmd_anonymous_page(vmf);
	if (vmf->vma->vm_ops->huge_fault)
		return vmf->vma->vm_ops->huge_fault(vmf, PE_SIZE_PMD);
	return VM_FAULT_FALLBACK;
}