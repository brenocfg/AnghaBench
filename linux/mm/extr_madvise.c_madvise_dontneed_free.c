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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; } ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 long EINVAL ; 
 long ENOMEM ; 
 int MADV_DONTNEED ; 
 int MADV_FREE ; 
 int /*<<< orphan*/  VM_WARN_ON (int) ; 
 int /*<<< orphan*/  can_madv_lru_vma (struct vm_area_struct*) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (TYPE_1__*,unsigned long) ; 
 long madvise_dontneed_single_vma (struct vm_area_struct*,unsigned long,unsigned long) ; 
 long madvise_free_single_vma (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  userfaultfd_remove (struct vm_area_struct*,unsigned long,unsigned long) ; 

__attribute__((used)) static long madvise_dontneed_free(struct vm_area_struct *vma,
				  struct vm_area_struct **prev,
				  unsigned long start, unsigned long end,
				  int behavior)
{
	*prev = vma;
	if (!can_madv_lru_vma(vma))
		return -EINVAL;

	if (!userfaultfd_remove(vma, start, end)) {
		*prev = NULL; /* mmap_sem has been dropped, prev is stale */

		down_read(&current->mm->mmap_sem);
		vma = find_vma(current->mm, start);
		if (!vma)
			return -ENOMEM;
		if (start < vma->vm_start) {
			/*
			 * This "vma" under revalidation is the one
			 * with the lowest vma->vm_start where start
			 * is also < vma->vm_end. If start <
			 * vma->vm_start it means an hole materialized
			 * in the user address space within the
			 * virtual range passed to MADV_DONTNEED
			 * or MADV_FREE.
			 */
			return -ENOMEM;
		}
		if (!can_madv_lru_vma(vma))
			return -EINVAL;
		if (end > vma->vm_end) {
			/*
			 * Don't fail if end > vma->vm_end. If the old
			 * vma was splitted while the mmap_sem was
			 * released the effect of the concurrent
			 * operation may not cause madvise() to
			 * have an undefined result. There may be an
			 * adjacent next vma that we'll walk
			 * next. userfaultfd_remove() will generate an
			 * UFFD_EVENT_REMOVE repetition on the
			 * end-vma->vm_end range, but the manager can
			 * handle a repetition fine.
			 */
			end = vma->vm_end;
		}
		VM_WARN_ON(start >= end);
	}

	if (behavior == MADV_DONTNEED)
		return madvise_dontneed_single_vma(vma, start, end);
	else if (behavior == MADV_FREE)
		return madvise_free_single_vma(vma, start, end);
	else
		return -EINVAL;
}