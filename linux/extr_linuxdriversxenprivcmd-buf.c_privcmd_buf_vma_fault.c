#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_fault_t ;
struct vm_fault {scalar_t__ address; int /*<<< orphan*/  pgoff; TYPE_1__* vma; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  pr_debug (char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static vm_fault_t privcmd_buf_vma_fault(struct vm_fault *vmf)
{
	pr_debug("fault: vma=%p %lx-%lx, pgoff=%lx, uv=%p\n",
		 vmf->vma, vmf->vma->vm_start, vmf->vma->vm_end,
		 vmf->pgoff, (void *)vmf->address);

	return VM_FAULT_SIGBUS;
}