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
struct vm_area_struct {int vm_flags; unsigned long vm_start; unsigned long vm_end; struct mm_struct* vm_mm; } ;
struct mm_struct {unsigned long locked_vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 int EFAULT ; 
 int ENOMEM ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIMIT_STACK ; 
 int VM_GROWSUP ; 
 int VM_LOCKED ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ is_hugepage_only_range (struct mm_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  may_expand_vm (struct mm_struct*,int,unsigned long) ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 
 scalar_t__ security_vm_enough_memory_mm (struct mm_struct*,unsigned long) ; 

__attribute__((used)) static int acct_stack_growth(struct vm_area_struct *vma,
			     unsigned long size, unsigned long grow)
{
	struct mm_struct *mm = vma->vm_mm;
	unsigned long new_start;

	/* address space limit tests */
	if (!may_expand_vm(mm, vma->vm_flags, grow))
		return -ENOMEM;

	/* Stack limit test */
	if (size > rlimit(RLIMIT_STACK))
		return -ENOMEM;

	/* mlock limit tests */
	if (vma->vm_flags & VM_LOCKED) {
		unsigned long locked;
		unsigned long limit;
		locked = mm->locked_vm + grow;
		limit = rlimit(RLIMIT_MEMLOCK);
		limit >>= PAGE_SHIFT;
		if (locked > limit && !capable(CAP_IPC_LOCK))
			return -ENOMEM;
	}

	/* Check to ensure the stack will not grow into a hugetlb-only region */
	new_start = (vma->vm_flags & VM_GROWSUP) ? vma->vm_start :
			vma->vm_end - size;
	if (is_hugepage_only_range(vma->vm_mm, new_start, size))
		return -EFAULT;

	/*
	 * Overcommit..  This must be the final test, as it will
	 * update security statistics.
	 */
	if (security_vm_enough_memory_mm(mm, grow))
		return -ENOMEM;

	return 0;
}