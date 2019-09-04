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
 long PAGE_SHIFT ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,long,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rlimit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void decrement_locked_vm(struct mm_struct *mm, long npages)
{
	if (!mm || !npages)
		return;

	down_write(&mm->mmap_sem);
	if (WARN_ON_ONCE(npages > mm->locked_vm))
		npages = mm->locked_vm;
	mm->locked_vm -= npages;
	pr_debug("[%d] RLIMIT_MEMLOCK -%ld %ld/%ld\n", current->pid,
			npages << PAGE_SHIFT,
			mm->locked_vm << PAGE_SHIFT,
			rlimit(RLIMIT_MEMLOCK));
	up_write(&mm->mmap_sem);
}