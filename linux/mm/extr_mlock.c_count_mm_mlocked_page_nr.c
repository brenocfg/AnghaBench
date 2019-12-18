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
struct vm_area_struct {unsigned long vm_end; unsigned long vm_start; int vm_flags; struct vm_area_struct* vm_next; } ;
struct mm_struct {struct vm_area_struct* mmap; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int VM_LOCKED ; 
 TYPE_1__* current ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 

__attribute__((used)) static unsigned long count_mm_mlocked_page_nr(struct mm_struct *mm,
		unsigned long start, size_t len)
{
	struct vm_area_struct *vma;
	unsigned long count = 0;

	if (mm == NULL)
		mm = current->mm;

	vma = find_vma(mm, start);
	if (vma == NULL)
		vma = mm->mmap;

	for (; vma ; vma = vma->vm_next) {
		if (start >= vma->vm_end)
			continue;
		if (start + len <=  vma->vm_start)
			break;
		if (vma->vm_flags & VM_LOCKED) {
			if (start > vma->vm_start)
				count -= (start - vma->vm_start);
			if (start + len < vma->vm_end) {
				count += start + len - vma->vm_start;
				break;
			}
			count += vma->vm_end - vma->vm_start;
		}
	}

	return count >> PAGE_SHIFT;
}