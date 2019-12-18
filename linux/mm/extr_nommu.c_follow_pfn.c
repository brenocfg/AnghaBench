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
struct vm_area_struct {int vm_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 int VM_IO ; 
 int VM_PFNMAP ; 

int follow_pfn(struct vm_area_struct *vma, unsigned long address,
	unsigned long *pfn)
{
	if (!(vma->vm_flags & (VM_IO | VM_PFNMAP)))
		return -EINVAL;

	*pfn = address >> PAGE_SHIFT;
	return 0;
}