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
struct vm_area_struct {scalar_t__ vm_start; scalar_t__ vm_end; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int remap_vmalloc_range_partial (struct vm_area_struct*,scalar_t__,void*,scalar_t__) ; 

int remap_vmalloc_range(struct vm_area_struct *vma, void *addr,
						unsigned long pgoff)
{
	return remap_vmalloc_range_partial(vma, vma->vm_start,
					   addr + (pgoff << PAGE_SHIFT),
					   vma->vm_end - vma->vm_start);
}