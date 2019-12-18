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
struct task_struct {unsigned long exit_code; TYPE_1__* sighand; } ;
struct TYPE_2__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int EIO ; 
 long PTRACE_SYSCALL ; 
 long PTRACE_SYSEMU ; 
 long PTRACE_SYSEMU_SINGLESTEP ; 
 int /*<<< orphan*/  TIF_SYSCALL_EMU ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  __TASK_TRACED ; 
 int /*<<< orphan*/  arch_has_block_step () ; 
 int /*<<< orphan*/  arch_has_single_step () ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ is_singleblock (long) ; 
 scalar_t__ is_singlestep (long) ; 
 scalar_t__ is_sysemu_singlestep (long) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_group_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  user_disable_single_step (struct task_struct*) ; 
 int /*<<< orphan*/  user_enable_block_step (struct task_struct*) ; 
 int /*<<< orphan*/  user_enable_single_step (struct task_struct*) ; 
 int /*<<< orphan*/  valid_signal (unsigned long) ; 
 int /*<<< orphan*/  wake_up_state (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ptrace_resume(struct task_struct *child, long request,
			 unsigned long data)
{
	bool need_siglock;

	if (!valid_signal(data))
		return -EIO;

	if (request == PTRACE_SYSCALL)
		set_tsk_thread_flag(child, TIF_SYSCALL_TRACE);
	else
		clear_tsk_thread_flag(child, TIF_SYSCALL_TRACE);

#ifdef TIF_SYSCALL_EMU
	if (request == PTRACE_SYSEMU || request == PTRACE_SYSEMU_SINGLESTEP)
		set_tsk_thread_flag(child, TIF_SYSCALL_EMU);
	else
		clear_tsk_thread_flag(child, TIF_SYSCALL_EMU);
#endif

	if (is_singleblock(request)) {
		if (unlikely(!arch_has_block_step()))
			return -EIO;
		user_enable_block_step(child);
	} else if (is_singlestep(request) || is_sysemu_singlestep(request)) {
		if (unlikely(!arch_has_single_step()))
			return -EIO;
		user_enable_single_step(child);
	} else {
		user_disable_single_step(child);
	}

	/*
	 * Change ->exit_code and ->state under siglock to avoid the race
	 * with wait_task_stopped() in between; a non-zero ->exit_code will
	 * wrongly look like another report from tracee.
	 *
	 * Note that we need siglock even if ->exit_code == data and/or this
	 * status was not reported yet, the new status must not be cleared by
	 * wait_task_stopped() after resume.
	 *
	 * If data == 0 we do not care if wait_task_stopped() reports the old
	 * status and clears the code too; this can't race with the tracee, it
	 * takes siglock after resume.
	 */
	need_siglock = data && !thread_group_empty(current);
	if (need_siglock)
		spin_lock_irq(&child->sighand->siglock);
	child->exit_code = data;
	wake_up_state(child, __TASK_TRACED);
	if (need_siglock)
		spin_unlock_irq(&child->sighand->siglock);

	return 0;
}