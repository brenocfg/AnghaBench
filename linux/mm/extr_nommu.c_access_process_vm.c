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
struct task_struct {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int __access_remote_vm (struct task_struct*,struct mm_struct*,unsigned long,void*,int,unsigned int) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 

int access_process_vm(struct task_struct *tsk, unsigned long addr, void *buf, int len,
		unsigned int gup_flags)
{
	struct mm_struct *mm;

	if (addr + len < addr)
		return 0;

	mm = get_task_mm(tsk);
	if (!mm)
		return 0;

	len = __access_remote_vm(tsk, mm, addr, buf, len, gup_flags);

	mmput(mm);
	return len;
}