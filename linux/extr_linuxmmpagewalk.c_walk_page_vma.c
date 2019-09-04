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
struct vm_area_struct {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; } ;
struct mm_walk {struct vm_area_struct* vma; TYPE_1__* mm; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int __walk_page_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mm_walk*) ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 
 int walk_page_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mm_walk*) ; 

int walk_page_vma(struct vm_area_struct *vma, struct mm_walk *walk)
{
	int err;

	if (!walk->mm)
		return -EINVAL;

	VM_BUG_ON(!rwsem_is_locked(&walk->mm->mmap_sem));
	VM_BUG_ON(!vma);
	walk->vma = vma;
	err = walk_page_test(vma->vm_start, vma->vm_end, walk);
	if (err > 0)
		return 0;
	if (err < 0)
		return err;
	return __walk_page_range(vma->vm_start, vma->vm_end, walk);
}