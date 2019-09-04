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
struct vm_area_struct {int vm_flags; void* vm_private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON_VMA (int,struct vm_area_struct*) ; 
 int VM_MAYSHARE ; 
 int /*<<< orphan*/  is_vm_hugetlb_page (struct vm_area_struct*) ; 

void reset_vma_resv_huge_pages(struct vm_area_struct *vma)
{
	VM_BUG_ON_VMA(!is_vm_hugetlb_page(vma), vma);
	if (!(vma->vm_flags & VM_MAYSHARE))
		vma->vm_private_data = (void *)0;
}