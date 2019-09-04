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
struct vm_area_struct {unsigned long vm_end; struct vm_area_struct* vm_next; int /*<<< orphan*/  vm_page_prot; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ is_normal_memory (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __check_mem_type(struct vm_area_struct *vma, unsigned long end)
{
	while (vma && is_normal_memory(vma->vm_page_prot)) {
		if (vma->vm_end >= end)
			return 0;
		vma = vma->vm_next;
	}

	return -EINVAL;
}