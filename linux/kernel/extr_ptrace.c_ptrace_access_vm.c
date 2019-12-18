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
struct task_struct {scalar_t__ parent; int /*<<< orphan*/  ptrace; } ;
struct mm_struct {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 scalar_t__ SUID_DUMP_USER ; 
 int __access_remote_vm (struct task_struct*,struct mm_struct*,unsigned long,void*,int,unsigned int) ; 
 scalar_t__ current ; 
 scalar_t__ get_dumpable (struct mm_struct*) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  ptracer_capable (struct task_struct*,int /*<<< orphan*/ ) ; 

int ptrace_access_vm(struct task_struct *tsk, unsigned long addr,
		     void *buf, int len, unsigned int gup_flags)
{
	struct mm_struct *mm;
	int ret;

	mm = get_task_mm(tsk);
	if (!mm)
		return 0;

	if (!tsk->ptrace ||
	    (current != tsk->parent) ||
	    ((get_dumpable(mm) != SUID_DUMP_USER) &&
	     !ptracer_capable(tsk, mm->user_ns))) {
		mmput(mm);
		return 0;
	}

	ret = __access_remote_vm(tsk, mm, addr, buf, len, gup_flags);
	mmput(mm);

	return ret;
}