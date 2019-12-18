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
typedef  int /*<<< orphan*/  uid_t ;
struct waitid_info {int cause; int status; int pid; int /*<<< orphan*/  uid; } ;
struct wait_opts {int wo_flags; int wo_stat; struct waitid_info* wo_info; scalar_t__ wo_rusage; } ;
struct task_struct {TYPE_1__* sighand; } ;
typedef  int pid_t ;
struct TYPE_2__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int CLD_STOPPED ; 
 int CLD_TRAPPED ; 
 int /*<<< orphan*/  RUSAGE_BOTH ; 
 int WNOWAIT ; 
 int WUNTRACED ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  getrusage (struct task_struct*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_annotate_sleep () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int task_pid_vnr (struct task_struct*) ; 
 int* task_stopped_code (struct task_struct*,int) ; 
 int /*<<< orphan*/  task_uid (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int wait_task_stopped(struct wait_opts *wo,
				int ptrace, struct task_struct *p)
{
	struct waitid_info *infop;
	int exit_code, *p_code, why;
	uid_t uid = 0; /* unneeded, required by compiler */
	pid_t pid;

	/*
	 * Traditionally we see ptrace'd stopped tasks regardless of options.
	 */
	if (!ptrace && !(wo->wo_flags & WUNTRACED))
		return 0;

	if (!task_stopped_code(p, ptrace))
		return 0;

	exit_code = 0;
	spin_lock_irq(&p->sighand->siglock);

	p_code = task_stopped_code(p, ptrace);
	if (unlikely(!p_code))
		goto unlock_sig;

	exit_code = *p_code;
	if (!exit_code)
		goto unlock_sig;

	if (!unlikely(wo->wo_flags & WNOWAIT))
		*p_code = 0;

	uid = from_kuid_munged(current_user_ns(), task_uid(p));
unlock_sig:
	spin_unlock_irq(&p->sighand->siglock);
	if (!exit_code)
		return 0;

	/*
	 * Now we are pretty sure this task is interesting.
	 * Make sure it doesn't get reaped out from under us while we
	 * give up the lock and then examine it below.  We don't want to
	 * keep holding onto the tasklist_lock while we call getrusage and
	 * possibly take page faults for user memory.
	 */
	get_task_struct(p);
	pid = task_pid_vnr(p);
	why = ptrace ? CLD_TRAPPED : CLD_STOPPED;
	read_unlock(&tasklist_lock);
	sched_annotate_sleep();
	if (wo->wo_rusage)
		getrusage(p, RUSAGE_BOTH, wo->wo_rusage);
	put_task_struct(p);

	if (likely(!(wo->wo_flags & WNOWAIT)))
		wo->wo_stat = (exit_code << 8) | 0x7f;

	infop = wo->wo_info;
	if (infop) {
		infop->cause = why;
		infop->status = exit_code;
		infop->pid = pid;
		infop->uid = uid;
	}
	return pid;
}