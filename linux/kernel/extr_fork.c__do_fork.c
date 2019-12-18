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
typedef  int u64 ;
struct task_struct {struct completion* vfork_done; } ;
struct pid {int dummy; } ;
struct kernel_clone_args {int flags; scalar_t__ exit_signal; int /*<<< orphan*/  parent_tid; } ;
struct completion {int dummy; } ;

/* Variables and functions */
 int CLONE_PARENT_SETTID ; 
 int CLONE_UNTRACED ; 
 int CLONE_VFORK ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int /*<<< orphan*/  NUMA_NO_NODE ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int PTRACE_EVENT_CLONE ; 
 int PTRACE_EVENT_FORK ; 
 int PTRACE_EVENT_VFORK ; 
 int PTRACE_EVENT_VFORK_DONE ; 
 long PTR_ERR (struct task_struct*) ; 
 scalar_t__ SIGCHLD ; 
 int /*<<< orphan*/  add_latent_entropy () ; 
 struct task_struct* copy_process (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct kernel_clone_args*) ; 
 int /*<<< orphan*/  current ; 
 struct pid* get_task_pid (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  init_completion (struct completion*) ; 
 scalar_t__ likely (int) ; 
 long pid_vnr (struct pid*) ; 
 int /*<<< orphan*/  ptrace_event_enabled (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptrace_event_pid (int,struct pid*) ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 int /*<<< orphan*/  put_user (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_sched_process_fork (int /*<<< orphan*/ ,struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wait_for_vfork_done (struct task_struct*,struct completion*) ; 
 int /*<<< orphan*/  wake_up_new_task (struct task_struct*) ; 

long _do_fork(struct kernel_clone_args *args)
{
	u64 clone_flags = args->flags;
	struct completion vfork;
	struct pid *pid;
	struct task_struct *p;
	int trace = 0;
	long nr;

	/*
	 * Determine whether and which event to report to ptracer.  When
	 * called from kernel_thread or CLONE_UNTRACED is explicitly
	 * requested, no event is reported; otherwise, report if the event
	 * for the type of forking is enabled.
	 */
	if (!(clone_flags & CLONE_UNTRACED)) {
		if (clone_flags & CLONE_VFORK)
			trace = PTRACE_EVENT_VFORK;
		else if (args->exit_signal != SIGCHLD)
			trace = PTRACE_EVENT_CLONE;
		else
			trace = PTRACE_EVENT_FORK;

		if (likely(!ptrace_event_enabled(current, trace)))
			trace = 0;
	}

	p = copy_process(NULL, trace, NUMA_NO_NODE, args);
	add_latent_entropy();

	if (IS_ERR(p))
		return PTR_ERR(p);

	/*
	 * Do this prior waking up the new thread - the thread pointer
	 * might get invalid after that point, if the thread exits quickly.
	 */
	trace_sched_process_fork(current, p);

	pid = get_task_pid(p, PIDTYPE_PID);
	nr = pid_vnr(pid);

	if (clone_flags & CLONE_PARENT_SETTID)
		put_user(nr, args->parent_tid);

	if (clone_flags & CLONE_VFORK) {
		p->vfork_done = &vfork;
		init_completion(&vfork);
		get_task_struct(p);
	}

	wake_up_new_task(p);

	/* forking complete and child started to run, tell ptracer */
	if (unlikely(trace))
		ptrace_event_pid(trace, pid);

	if (clone_flags & CLONE_VFORK) {
		if (!wait_for_vfork_done(p, &vfork))
			ptrace_event_pid(PTRACE_EVENT_VFORK_DONE, pid);
	}

	put_pid(pid);
	return nr;
}