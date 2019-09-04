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
struct vm_fault {scalar_t__ address; int /*<<< orphan*/  page; struct vm_area_struct* vma; } ;
struct vm_area_struct {scalar_t__ vm_start; struct mdev_state* vm_private_data; } ;
struct mdev_state {scalar_t__ pagecount; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  mbochs_get_page (struct mdev_state*,scalar_t__) ; 

__attribute__((used)) static vm_fault_t mbochs_region_vm_fault(struct vm_fault *vmf)
{
	struct vm_area_struct *vma = vmf->vma;
	struct mdev_state *mdev_state = vma->vm_private_data;
	pgoff_t page_offset = (vmf->address - vma->vm_start) >> PAGE_SHIFT;

	if (page_offset >= mdev_state->pagecount)
		return VM_FAULT_SIGBUS;

	vmf->page = mbochs_get_page(mdev_state, page_offset);
	if (!vmf->page)
		return VM_FAULT_SIGBUS;

	return 0;
}