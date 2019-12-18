#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {unsigned long vm_start; int vm_flags; unsigned long vm_end; struct vm_area_struct* vm_next; struct vm_area_struct* vm_prev; } ;
struct TYPE_5__ {int personality; TYPE_1__* mm; } ;
struct TYPE_4__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int EACCES ; 
 int EINTR ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t PAGE_ALIGN (size_t) ; 
 unsigned long PAGE_MASK ; 
 unsigned long PROT_EXEC ; 
 unsigned long PROT_GROWSDOWN ; 
 unsigned long PROT_GROWSUP ; 
 unsigned long PROT_READ ; 
 int READ_IMPLIES_EXEC ; 
 unsigned long VM_EXEC ; 
 unsigned long VM_FLAGS_CLEAR ; 
 int VM_GROWSDOWN ; 
 int VM_GROWSUP ; 
 int VM_MAYEXEC ; 
 unsigned long VM_READ ; 
 unsigned long VM_WRITE ; 
 int arch_override_mprotect_pkey (struct vm_area_struct*,unsigned long,int) ; 
 int /*<<< orphan*/  arch_validate_prot (unsigned long,unsigned long) ; 
 unsigned long calc_vm_prot_bits (unsigned long,int) ; 
 TYPE_3__* current ; 
 scalar_t__ down_write_killable (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  mm_pkey_is_allocated (TYPE_1__*,int) ; 
 int mprotect_fixup (struct vm_area_struct*,struct vm_area_struct**,unsigned long,unsigned long,unsigned long) ; 
 int security_file_mprotect (struct vm_area_struct*,unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int const) ; 
 unsigned long untagged_addr (unsigned long) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_mprotect_pkey(unsigned long start, size_t len,
		unsigned long prot, int pkey)
{
	unsigned long nstart, end, tmp, reqprot;
	struct vm_area_struct *vma, *prev;
	int error = -EINVAL;
	const int grows = prot & (PROT_GROWSDOWN|PROT_GROWSUP);
	const bool rier = (current->personality & READ_IMPLIES_EXEC) &&
				(prot & PROT_READ);

	start = untagged_addr(start);

	prot &= ~(PROT_GROWSDOWN|PROT_GROWSUP);
	if (grows == (PROT_GROWSDOWN|PROT_GROWSUP)) /* can't be both */
		return -EINVAL;

	if (start & ~PAGE_MASK)
		return -EINVAL;
	if (!len)
		return 0;
	len = PAGE_ALIGN(len);
	end = start + len;
	if (end <= start)
		return -ENOMEM;
	if (!arch_validate_prot(prot, start))
		return -EINVAL;

	reqprot = prot;

	if (down_write_killable(&current->mm->mmap_sem))
		return -EINTR;

	/*
	 * If userspace did not allocate the pkey, do not let
	 * them use it here.
	 */
	error = -EINVAL;
	if ((pkey != -1) && !mm_pkey_is_allocated(current->mm, pkey))
		goto out;

	vma = find_vma(current->mm, start);
	error = -ENOMEM;
	if (!vma)
		goto out;
	prev = vma->vm_prev;
	if (unlikely(grows & PROT_GROWSDOWN)) {
		if (vma->vm_start >= end)
			goto out;
		start = vma->vm_start;
		error = -EINVAL;
		if (!(vma->vm_flags & VM_GROWSDOWN))
			goto out;
	} else {
		if (vma->vm_start > start)
			goto out;
		if (unlikely(grows & PROT_GROWSUP)) {
			end = vma->vm_end;
			error = -EINVAL;
			if (!(vma->vm_flags & VM_GROWSUP))
				goto out;
		}
	}
	if (start > vma->vm_start)
		prev = vma;

	for (nstart = start ; ; ) {
		unsigned long mask_off_old_flags;
		unsigned long newflags;
		int new_vma_pkey;

		/* Here we know that vma->vm_start <= nstart < vma->vm_end. */

		/* Does the application expect PROT_READ to imply PROT_EXEC */
		if (rier && (vma->vm_flags & VM_MAYEXEC))
			prot |= PROT_EXEC;

		/*
		 * Each mprotect() call explicitly passes r/w/x permissions.
		 * If a permission is not passed to mprotect(), it must be
		 * cleared from the VMA.
		 */
		mask_off_old_flags = VM_READ | VM_WRITE | VM_EXEC |
					VM_FLAGS_CLEAR;

		new_vma_pkey = arch_override_mprotect_pkey(vma, prot, pkey);
		newflags = calc_vm_prot_bits(prot, new_vma_pkey);
		newflags |= (vma->vm_flags & ~mask_off_old_flags);

		/* newflags >> 4 shift VM_MAY% in place of VM_% */
		if ((newflags & ~(newflags >> 4)) & (VM_READ | VM_WRITE | VM_EXEC)) {
			error = -EACCES;
			goto out;
		}

		error = security_file_mprotect(vma, reqprot, prot);
		if (error)
			goto out;

		tmp = vma->vm_end;
		if (tmp > end)
			tmp = end;
		error = mprotect_fixup(vma, &prev, nstart, tmp, newflags);
		if (error)
			goto out;
		nstart = tmp;

		if (nstart < prev->vm_end)
			nstart = prev->vm_end;
		if (nstart >= end)
			goto out;

		vma = prev->vm_next;
		if (!vma || vma->vm_start != nstart) {
			error = -ENOMEM;
			goto out;
		}
		prot = reqprot;
	}
out:
	up_write(&current->mm->mmap_sem);
	return error;
}