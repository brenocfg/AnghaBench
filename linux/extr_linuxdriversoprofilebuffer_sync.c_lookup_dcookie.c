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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; unsigned long vm_pgoff; TYPE_1__* vm_file; struct vm_area_struct* vm_next; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
typedef  unsigned long off_t ;
struct TYPE_2__ {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 unsigned long INVALID_COOKIE ; 
 unsigned long NO_COOKIE ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 unsigned long fast_get_dcookie (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long
lookup_dcookie(struct mm_struct *mm, unsigned long addr, off_t *offset)
{
	unsigned long cookie = NO_COOKIE;
	struct vm_area_struct *vma;

	down_read(&mm->mmap_sem);
	for (vma = find_vma(mm, addr); vma; vma = vma->vm_next) {

		if (addr < vma->vm_start || addr >= vma->vm_end)
			continue;

		if (vma->vm_file) {
			cookie = fast_get_dcookie(&vma->vm_file->f_path);
			*offset = (vma->vm_pgoff << PAGE_SHIFT) + addr -
				vma->vm_start;
		} else {
			/* must be an anonymous map */
			*offset = addr;
		}

		break;
	}

	if (!vma)
		cookie = INVALID_COOKIE;
	up_read(&mm->mmap_sem);

	return cookie;
}