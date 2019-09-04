#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; struct vm_area_struct* vm_next; } ;
struct mm_walk {scalar_t__ pte_hole; struct vm_area_struct* vma; TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VM_BUG_ON_MM (int,TYPE_1__*) ; 
 int __walk_page_range (unsigned long,unsigned long,struct mm_walk*) ; 
 struct vm_area_struct* find_vma (TYPE_1__*,unsigned long) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 
 int walk_page_test (unsigned long,unsigned long,struct mm_walk*) ; 

int walk_page_range(unsigned long start, unsigned long end,
		    struct mm_walk *walk)
{
	int err = 0;
	unsigned long next;
	struct vm_area_struct *vma;

	if (start >= end)
		return -EINVAL;

	if (!walk->mm)
		return -EINVAL;

	VM_BUG_ON_MM(!rwsem_is_locked(&walk->mm->mmap_sem), walk->mm);

	vma = find_vma(walk->mm, start);
	do {
		if (!vma) { /* after the last vma */
			walk->vma = NULL;
			next = end;
		} else if (start < vma->vm_start) { /* outside vma */
			walk->vma = NULL;
			next = min(end, vma->vm_start);
		} else { /* inside vma */
			walk->vma = vma;
			next = min(end, vma->vm_end);
			vma = vma->vm_next;

			err = walk_page_test(start, next, walk);
			if (err > 0) {
				/*
				 * positive return values are purely for
				 * controlling the pagewalk, so should never
				 * be passed to the callers.
				 */
				err = 0;
				continue;
			}
			if (err < 0)
				break;
		}
		if (walk->vma || walk->pte_hole)
			err = __walk_page_range(start, next, walk);
		if (err)
			break;
	} while (start = next, start < end);
	return err;
}