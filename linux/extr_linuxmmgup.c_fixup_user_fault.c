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
typedef  int vm_fault_t ;
struct vm_area_struct {unsigned long vm_start; } ;
struct task_struct {int /*<<< orphan*/  min_flt; int /*<<< orphan*/  maj_flt; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EFAULT ; 
 unsigned int FAULT_FLAG_ALLOW_RETRY ; 
 unsigned int FAULT_FLAG_TRIED ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_MAJOR ; 
 int VM_FAULT_RETRY ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_extend_vma (struct mm_struct*,unsigned long) ; 
 int handle_mm_fault (struct vm_area_struct*,unsigned long,unsigned int) ; 
 int vm_fault_to_errno (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_permits_fault (struct vm_area_struct*,unsigned int) ; 

int fixup_user_fault(struct task_struct *tsk, struct mm_struct *mm,
		     unsigned long address, unsigned int fault_flags,
		     bool *unlocked)
{
	struct vm_area_struct *vma;
	vm_fault_t ret, major = 0;

	if (unlocked)
		fault_flags |= FAULT_FLAG_ALLOW_RETRY;

retry:
	vma = find_extend_vma(mm, address);
	if (!vma || address < vma->vm_start)
		return -EFAULT;

	if (!vma_permits_fault(vma, fault_flags))
		return -EFAULT;

	ret = handle_mm_fault(vma, address, fault_flags);
	major |= ret & VM_FAULT_MAJOR;
	if (ret & VM_FAULT_ERROR) {
		int err = vm_fault_to_errno(ret, 0);

		if (err)
			return err;
		BUG();
	}

	if (ret & VM_FAULT_RETRY) {
		down_read(&mm->mmap_sem);
		if (!(fault_flags & FAULT_FLAG_TRIED)) {
			*unlocked = true;
			fault_flags &= ~FAULT_FLAG_ALLOW_RETRY;
			fault_flags |= FAULT_FLAG_TRIED;
			goto retry;
		}
	}

	if (tsk) {
		if (major)
			tsk->maj_flt++;
		else
			tsk->min_flt++;
	}
	return 0;
}