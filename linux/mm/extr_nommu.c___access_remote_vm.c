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
struct vm_area_struct {unsigned long vm_end; int vm_flags; } ;
struct task_struct {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 unsigned int FOLL_WRITE ; 
 int VM_MAYREAD ; 
 int VM_MAYWRITE ; 
 int /*<<< orphan*/  copy_from_user_page (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,void*,void*,int) ; 
 int /*<<< orphan*/  copy_to_user_page (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,void*,void*,int) ; 
 scalar_t__ down_read_killable (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int __access_remote_vm(struct task_struct *tsk, struct mm_struct *mm,
		unsigned long addr, void *buf, int len, unsigned int gup_flags)
{
	struct vm_area_struct *vma;
	int write = gup_flags & FOLL_WRITE;

	if (down_read_killable(&mm->mmap_sem))
		return 0;

	/* the access must start within one of the target process's mappings */
	vma = find_vma(mm, addr);
	if (vma) {
		/* don't overrun this mapping */
		if (addr + len >= vma->vm_end)
			len = vma->vm_end - addr;

		/* only read or write mappings where it is permitted */
		if (write && vma->vm_flags & VM_MAYWRITE)
			copy_to_user_page(vma, NULL, addr,
					 (void *) addr, buf, len);
		else if (!write && vma->vm_flags & VM_MAYREAD)
			copy_from_user_page(vma, NULL, addr,
					    buf, (void *) addr, len);
		else
			len = 0;
	} else {
		len = 0;
	}

	up_read(&mm->mmap_sem);

	return len;
}