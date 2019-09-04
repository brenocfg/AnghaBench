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
struct vm_area_struct {int vm_end; int vm_start; scalar_t__ vm_pgoff; int /*<<< orphan*/  vm_file; struct vm_area_struct* vm_next; } ;
struct uprobe {scalar_t__ inode; int offset; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; struct vm_area_struct* mmap; } ;
typedef  int loff_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ file_inode (int /*<<< orphan*/ ) ; 
 unsigned long offset_to_vaddr (struct vm_area_struct*,int) ; 
 int remove_breakpoint (struct uprobe*,struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  valid_vma (struct vm_area_struct*,int) ; 

__attribute__((used)) static int unapply_uprobe(struct uprobe *uprobe, struct mm_struct *mm)
{
	struct vm_area_struct *vma;
	int err = 0;

	down_read(&mm->mmap_sem);
	for (vma = mm->mmap; vma; vma = vma->vm_next) {
		unsigned long vaddr;
		loff_t offset;

		if (!valid_vma(vma, false) ||
		    file_inode(vma->vm_file) != uprobe->inode)
			continue;

		offset = (loff_t)vma->vm_pgoff << PAGE_SHIFT;
		if (uprobe->offset <  offset ||
		    uprobe->offset >= offset + vma->vm_end - vma->vm_start)
			continue;

		vaddr = offset_to_vaddr(vma, uprobe->offset);
		err |= remove_breakpoint(uprobe, mm, vaddr);
	}
	up_read(&mm->mmap_sem);

	return err;
}