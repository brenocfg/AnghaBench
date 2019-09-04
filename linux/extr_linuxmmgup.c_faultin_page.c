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
struct vm_area_struct {int vm_flags; } ;
struct task_struct {int /*<<< orphan*/  min_flt; int /*<<< orphan*/  maj_flt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EBUSY ; 
 int ENOENT ; 
 unsigned int FAULT_FLAG_ALLOW_RETRY ; 
 unsigned int FAULT_FLAG_REMOTE ; 
 unsigned int FAULT_FLAG_RETRY_NOWAIT ; 
 unsigned int FAULT_FLAG_TRIED ; 
 unsigned int FAULT_FLAG_WRITE ; 
 unsigned int FOLL_COW ; 
 unsigned int FOLL_MLOCK ; 
 unsigned int FOLL_NOWAIT ; 
 unsigned int FOLL_POPULATE ; 
 unsigned int FOLL_REMOTE ; 
 unsigned int FOLL_TRIED ; 
 unsigned int FOLL_WRITE ; 
 int VM_FAULT_ERROR ; 
 int VM_FAULT_MAJOR ; 
 int VM_FAULT_RETRY ; 
 int VM_FAULT_WRITE ; 
 int /*<<< orphan*/  VM_WARN_ON_ONCE (unsigned int) ; 
 int VM_WRITE ; 
 int handle_mm_fault (struct vm_area_struct*,unsigned long,unsigned int) ; 
 int vm_fault_to_errno (int,unsigned int) ; 

__attribute__((used)) static int faultin_page(struct task_struct *tsk, struct vm_area_struct *vma,
		unsigned long address, unsigned int *flags, int *nonblocking)
{
	unsigned int fault_flags = 0;
	vm_fault_t ret;

	/* mlock all present pages, but do not fault in new pages */
	if ((*flags & (FOLL_POPULATE | FOLL_MLOCK)) == FOLL_MLOCK)
		return -ENOENT;
	if (*flags & FOLL_WRITE)
		fault_flags |= FAULT_FLAG_WRITE;
	if (*flags & FOLL_REMOTE)
		fault_flags |= FAULT_FLAG_REMOTE;
	if (nonblocking)
		fault_flags |= FAULT_FLAG_ALLOW_RETRY;
	if (*flags & FOLL_NOWAIT)
		fault_flags |= FAULT_FLAG_ALLOW_RETRY | FAULT_FLAG_RETRY_NOWAIT;
	if (*flags & FOLL_TRIED) {
		VM_WARN_ON_ONCE(fault_flags & FAULT_FLAG_ALLOW_RETRY);
		fault_flags |= FAULT_FLAG_TRIED;
	}

	ret = handle_mm_fault(vma, address, fault_flags);
	if (ret & VM_FAULT_ERROR) {
		int err = vm_fault_to_errno(ret, *flags);

		if (err)
			return err;
		BUG();
	}

	if (tsk) {
		if (ret & VM_FAULT_MAJOR)
			tsk->maj_flt++;
		else
			tsk->min_flt++;
	}

	if (ret & VM_FAULT_RETRY) {
		if (nonblocking && !(fault_flags & FAULT_FLAG_RETRY_NOWAIT))
			*nonblocking = 0;
		return -EBUSY;
	}

	/*
	 * The VM_FAULT_WRITE bit tells us that do_wp_page has broken COW when
	 * necessary, even if maybe_mkwrite decided not to set pte_write. We
	 * can thus safely do subsequent page lookups as if they were reads.
	 * But only do so when looping for pte_write is futile: in some cases
	 * userspace may also be wanting to write to the gotten user page,
	 * which a read fault here might prevent (a readonly page might get
	 * reCOWed by userspace write).
	 */
	if ((ret & VM_FAULT_WRITE) && !(vma->vm_flags & VM_WRITE))
		*flags |= FOLL_COW;
	return 0;
}