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
struct mm_struct {scalar_t__ locked_vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 int EAGAIN ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 unsigned long VM_LOCKED ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int mlock_future_check(struct mm_struct *mm,
				     unsigned long flags,
				     unsigned long len)
{
	unsigned long locked, lock_limit;

	/*  mlock MCL_FUTURE? */
	if (flags & VM_LOCKED) {
		locked = len >> PAGE_SHIFT;
		locked += mm->locked_vm;
		lock_limit = rlimit(RLIMIT_MEMLOCK);
		lock_limit >>= PAGE_SHIFT;
		if (locked > lock_limit && !capable(CAP_IPC_LOCK))
			return -EAGAIN;
	}
	return 0;
}