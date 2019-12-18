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
struct vm_area_struct {unsigned long vm_start; int vm_flags; unsigned long vm_end; scalar_t__ vm_pgoff; } ;
struct mm_struct {unsigned long locked_vm; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct vm_area_struct* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int VM_ACCOUNT ; 
 int VM_DONTEXPAND ; 
 int VM_LOCKED ; 
 int VM_MAYSHARE ; 
 int VM_PFNMAP ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 struct vm_area_struct* find_vma (struct mm_struct*,unsigned long) ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 
 int /*<<< orphan*/  may_expand_vm (struct mm_struct*,int,unsigned long) ; 
 int /*<<< orphan*/  pr_warn_once (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 
 scalar_t__ security_vm_enough_memory_mm (struct mm_struct*,unsigned long) ; 

__attribute__((used)) static struct vm_area_struct *vma_to_resize(unsigned long addr,
	unsigned long old_len, unsigned long new_len, unsigned long *p)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma = find_vma(mm, addr);
	unsigned long pgoff;

	if (!vma || vma->vm_start > addr)
		return ERR_PTR(-EFAULT);

	/*
	 * !old_len is a special case where an attempt is made to 'duplicate'
	 * a mapping.  This makes no sense for private mappings as it will
	 * instead create a fresh/new mapping unrelated to the original.  This
	 * is contrary to the basic idea of mremap which creates new mappings
	 * based on the original.  There are no known use cases for this
	 * behavior.  As a result, fail such attempts.
	 */
	if (!old_len && !(vma->vm_flags & (VM_SHARED | VM_MAYSHARE))) {
		pr_warn_once("%s (%d): attempted to duplicate a private mapping with mremap.  This is not supported.\n", current->comm, current->pid);
		return ERR_PTR(-EINVAL);
	}

	if (is_vm_hugetlb_page(vma))
		return ERR_PTR(-EINVAL);

	/* We can't remap across vm area boundaries */
	if (old_len > vma->vm_end - addr)
		return ERR_PTR(-EFAULT);

	if (new_len == old_len)
		return vma;

	/* Need to be careful about a growing mapping */
	pgoff = (addr - vma->vm_start) >> PAGE_SHIFT;
	pgoff += vma->vm_pgoff;
	if (pgoff + (new_len >> PAGE_SHIFT) < pgoff)
		return ERR_PTR(-EINVAL);

	if (vma->vm_flags & (VM_DONTEXPAND | VM_PFNMAP))
		return ERR_PTR(-EFAULT);

	if (vma->vm_flags & VM_LOCKED) {
		unsigned long locked, lock_limit;
		locked = mm->locked_vm << PAGE_SHIFT;
		lock_limit = rlimit(RLIMIT_MEMLOCK);
		locked += new_len - old_len;
		if (locked > lock_limit && !capable(CAP_IPC_LOCK))
			return ERR_PTR(-EAGAIN);
	}

	if (!may_expand_vm(mm, vma->vm_flags,
				(new_len - old_len) >> PAGE_SHIFT))
		return ERR_PTR(-ENOMEM);

	if (vma->vm_flags & VM_ACCOUNT) {
		unsigned long charged = (new_len - old_len) >> PAGE_SHIFT;
		if (security_vm_enough_memory_mm(mm, charged))
			return ERR_PTR(-ENOMEM);
		*p = charged;
	}

	return vma;
}