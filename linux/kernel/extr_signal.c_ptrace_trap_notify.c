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
struct task_struct {int ptrace; int jobctl; TYPE_1__* sighand; } ;
struct TYPE_2__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int JOBCTL_LISTENING ; 
 int /*<<< orphan*/  JOBCTL_TRAP_NOTIFY ; 
 int PT_SEIZED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptrace_signal_wake_up (struct task_struct*,int) ; 
 int /*<<< orphan*/  task_set_jobctl_pending (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ptrace_trap_notify(struct task_struct *t)
{
	WARN_ON_ONCE(!(t->ptrace & PT_SEIZED));
	assert_spin_locked(&t->sighand->siglock);

	task_set_jobctl_pending(t, JOBCTL_TRAP_NOTIFY);
	ptrace_signal_wake_up(t, t->jobctl & JOBCTL_LISTENING);
}