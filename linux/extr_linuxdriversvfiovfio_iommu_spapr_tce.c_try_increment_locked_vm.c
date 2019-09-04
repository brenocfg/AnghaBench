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
struct mm_struct {long locked_vm; int /*<<< orphan*/  mmap_sem; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 long ENOMEM ; 
 long EPERM ; 
 long PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,long,long,long,char*) ; 
 long rlimit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long try_increment_locked_vm(struct mm_struct *mm, long npages)
{
	long ret = 0, locked, lock_limit;

	if (WARN_ON_ONCE(!mm))
		return -EPERM;

	if (!npages)
		return 0;

	down_write(&mm->mmap_sem);
	locked = mm->locked_vm + npages;
	lock_limit = rlimit(RLIMIT_MEMLOCK) >> PAGE_SHIFT;
	if (locked > lock_limit && !capable(CAP_IPC_LOCK))
		ret = -ENOMEM;
	else
		mm->locked_vm += npages;

	pr_debug("[%d] RLIMIT_MEMLOCK +%ld %ld/%ld%s\n", current->pid,
			npages << PAGE_SHIFT,
			mm->locked_vm << PAGE_SHIFT,
			rlimit(RLIMIT_MEMLOCK),
			ret ? " - exceeded" : "");

	up_write(&mm->mmap_sem);

	return ret;
}