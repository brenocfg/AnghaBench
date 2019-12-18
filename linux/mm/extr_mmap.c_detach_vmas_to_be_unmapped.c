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
struct vm_area_struct {unsigned long vm_start; struct vm_area_struct* vm_next; struct vm_area_struct* vm_prev; } ;
struct mm_struct {int /*<<< orphan*/  highest_vm_end; int /*<<< orphan*/  map_count; int /*<<< orphan*/  mm_rb; struct vm_area_struct* mmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  vm_end_gap (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_gap_update (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_rb_erase (struct vm_area_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmacache_invalidate (struct mm_struct*) ; 

__attribute__((used)) static void
detach_vmas_to_be_unmapped(struct mm_struct *mm, struct vm_area_struct *vma,
	struct vm_area_struct *prev, unsigned long end)
{
	struct vm_area_struct **insertion_point;
	struct vm_area_struct *tail_vma = NULL;

	insertion_point = (prev ? &prev->vm_next : &mm->mmap);
	vma->vm_prev = NULL;
	do {
		vma_rb_erase(vma, &mm->mm_rb);
		mm->map_count--;
		tail_vma = vma;
		vma = vma->vm_next;
	} while (vma && vma->vm_start < end);
	*insertion_point = vma;
	if (vma) {
		vma->vm_prev = prev;
		vma_gap_update(vma);
	} else
		mm->highest_vm_end = prev ? vm_end_gap(prev) : 0;
	tail_vma->vm_next = NULL;

	/* Kill the cache */
	vmacache_invalidate(mm);
}