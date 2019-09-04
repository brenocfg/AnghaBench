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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; int vm_flags; struct mm_struct* vm_mm; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int FOLL_FORCE ; 
 int FOLL_MLOCK ; 
 int FOLL_POPULATE ; 
 int FOLL_TOUCH ; 
 int FOLL_WRITE ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  VM_BUG_ON (unsigned long) ; 
 int /*<<< orphan*/  VM_BUG_ON_MM (int,struct mm_struct*) ; 
 int /*<<< orphan*/  VM_BUG_ON_VMA (int,struct vm_area_struct*) ; 
 int VM_EXEC ; 
 int VM_LOCKONFAULT ; 
 int VM_READ ; 
 int VM_SHARED ; 
 int VM_WRITE ; 
 long __get_user_pages (int /*<<< orphan*/ ,struct mm_struct*,unsigned long,unsigned long,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  rwsem_is_locked (int /*<<< orphan*/ *) ; 

long populate_vma_page_range(struct vm_area_struct *vma,
		unsigned long start, unsigned long end, int *nonblocking)
{
	struct mm_struct *mm = vma->vm_mm;
	unsigned long nr_pages = (end - start) / PAGE_SIZE;
	int gup_flags;

	VM_BUG_ON(start & ~PAGE_MASK);
	VM_BUG_ON(end   & ~PAGE_MASK);
	VM_BUG_ON_VMA(start < vma->vm_start, vma);
	VM_BUG_ON_VMA(end   > vma->vm_end, vma);
	VM_BUG_ON_MM(!rwsem_is_locked(&mm->mmap_sem), mm);

	gup_flags = FOLL_TOUCH | FOLL_POPULATE | FOLL_MLOCK;
	if (vma->vm_flags & VM_LOCKONFAULT)
		gup_flags &= ~FOLL_POPULATE;
	/*
	 * We want to touch writable mappings with a write fault in order
	 * to break COW, except for shared mappings because these don't COW
	 * and we would not want to dirty them for nothing.
	 */
	if ((vma->vm_flags & (VM_WRITE | VM_SHARED)) == VM_WRITE)
		gup_flags |= FOLL_WRITE;

	/*
	 * We want mlock to succeed for regions that have any permissions
	 * other than PROT_NONE.
	 */
	if (vma->vm_flags & (VM_READ | VM_WRITE | VM_EXEC))
		gup_flags |= FOLL_FORCE;

	/*
	 * We made sure addr is within a VMA, so the following will
	 * not result in a stack expansion that recurses back here.
	 */
	return __get_user_pages(current, mm, start, nr_pages, gup_flags,
				NULL, NULL, nonblocking);
}