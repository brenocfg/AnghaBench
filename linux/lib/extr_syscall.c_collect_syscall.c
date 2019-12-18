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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int nr; int /*<<< orphan*/ * args; int /*<<< orphan*/  instruction_pointer; } ;
struct syscall_info {TYPE_1__ data; int /*<<< orphan*/  sp; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  instruction_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  memset (struct syscall_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_task_stack (struct task_struct*) ; 
 int /*<<< orphan*/  syscall_get_arguments (struct task_struct*,struct pt_regs*,unsigned long*) ; 
 int syscall_get_nr (struct task_struct*,struct pt_regs*) ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 int /*<<< orphan*/  try_get_task_stack (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  user_stack_pointer (struct pt_regs*) ; 

__attribute__((used)) static int collect_syscall(struct task_struct *target, struct syscall_info *info)
{
	struct pt_regs *regs;

	if (!try_get_task_stack(target)) {
		/* Task has no stack, so the task isn't in a syscall. */
		memset(info, 0, sizeof(*info));
		info->data.nr = -1;
		return 0;
	}

	regs = task_pt_regs(target);
	if (unlikely(!regs)) {
		put_task_stack(target);
		return -EAGAIN;
	}

	info->sp = user_stack_pointer(regs);
	info->data.instruction_pointer = instruction_pointer(regs);

	info->data.nr = syscall_get_nr(target, regs);
	if (info->data.nr != -1L)
		syscall_get_arguments(target, regs,
				      (unsigned long *)&info->data.args[0]);

	put_task_stack(target);
	return 0;
}