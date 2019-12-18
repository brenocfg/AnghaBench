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
struct task_struct {scalar_t__ exit_state; int exit_signal; struct sighand_struct* sighand; int /*<<< orphan*/  parent; int /*<<< orphan*/  ptrace; struct task_struct* group_leader; int /*<<< orphan*/  sibling; int /*<<< orphan*/  tasks; int /*<<< orphan*/  pid; int /*<<< orphan*/  real_start_time; int /*<<< orphan*/  start_time; struct signal_struct* signal; } ;
struct signal_struct {int notify_count; struct task_struct* group_exit_task; } ;
struct sighand_struct {int /*<<< orphan*/  siglock; int /*<<< orphan*/  action; int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 scalar_t__ EXIT_DEAD ; 
 scalar_t__ EXIT_ZOMBIE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PIDTYPE_PGID ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  PIDTYPE_SID ; 
 int /*<<< orphan*/  PIDTYPE_TGID ; 
 void* SIGCHLD ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 int /*<<< orphan*/  __cleanup_sighand (struct sighand_struct*) ; 
 scalar_t__ __fatal_signal_pending (struct task_struct*) ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __wake_up_parent (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_threadgroup_change_begin (struct task_struct*) ; 
 int /*<<< orphan*/  cgroup_threadgroup_change_end (struct task_struct*) ; 
 int /*<<< orphan*/  change_pid (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_itimers (struct signal_struct*) ; 
 int /*<<< orphan*/  flush_itimer_signals () ; 
 int has_group_leader_pid (struct task_struct*) ; 
 struct sighand_struct* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (scalar_t__) ; 
 int /*<<< orphan*/  list_replace_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_replace_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct sighand_struct*,struct sighand_struct*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  release_task (struct task_struct*) ; 
 int /*<<< orphan*/  same_thread_group (struct task_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  sighand_cachep ; 
 scalar_t__ signal_group_exit (struct signal_struct*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 scalar_t__ thread_group_empty (struct task_struct*) ; 
 int /*<<< orphan*/  thread_group_leader (struct task_struct*) ; 
 int /*<<< orphan*/  transfer_pid (struct task_struct*,struct task_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 
 int zap_other_threads (struct task_struct*) ; 

__attribute__((used)) static int de_thread(struct task_struct *tsk)
{
	struct signal_struct *sig = tsk->signal;
	struct sighand_struct *oldsighand = tsk->sighand;
	spinlock_t *lock = &oldsighand->siglock;

	if (thread_group_empty(tsk))
		goto no_thread_group;

	/*
	 * Kill all other threads in the thread group.
	 */
	spin_lock_irq(lock);
	if (signal_group_exit(sig)) {
		/*
		 * Another group action in progress, just
		 * return so that the signal is processed.
		 */
		spin_unlock_irq(lock);
		return -EAGAIN;
	}

	sig->group_exit_task = tsk;
	sig->notify_count = zap_other_threads(tsk);
	if (!thread_group_leader(tsk))
		sig->notify_count--;

	while (sig->notify_count) {
		__set_current_state(TASK_KILLABLE);
		spin_unlock_irq(lock);
		schedule();
		if (__fatal_signal_pending(tsk))
			goto killed;
		spin_lock_irq(lock);
	}
	spin_unlock_irq(lock);

	/*
	 * At this point all other threads have exited, all we have to
	 * do is to wait for the thread group leader to become inactive,
	 * and to assume its PID:
	 */
	if (!thread_group_leader(tsk)) {
		struct task_struct *leader = tsk->group_leader;

		for (;;) {
			cgroup_threadgroup_change_begin(tsk);
			write_lock_irq(&tasklist_lock);
			/*
			 * Do this under tasklist_lock to ensure that
			 * exit_notify() can't miss ->group_exit_task
			 */
			sig->notify_count = -1;
			if (likely(leader->exit_state))
				break;
			__set_current_state(TASK_KILLABLE);
			write_unlock_irq(&tasklist_lock);
			cgroup_threadgroup_change_end(tsk);
			schedule();
			if (__fatal_signal_pending(tsk))
				goto killed;
		}

		/*
		 * The only record we have of the real-time age of a
		 * process, regardless of execs it's done, is start_time.
		 * All the past CPU time is accumulated in signal_struct
		 * from sister threads now dead.  But in this non-leader
		 * exec, nothing survives from the original leader thread,
		 * whose birth marks the true age of this process now.
		 * When we take on its identity by switching to its PID, we
		 * also take its birthdate (always earlier than our own).
		 */
		tsk->start_time = leader->start_time;
		tsk->real_start_time = leader->real_start_time;

		BUG_ON(!same_thread_group(leader, tsk));
		BUG_ON(has_group_leader_pid(tsk));
		/*
		 * An exec() starts a new thread group with the
		 * TGID of the previous thread group. Rehash the
		 * two threads with a switched PID, and release
		 * the former thread group leader:
		 */

		/* Become a process group leader with the old leader's pid.
		 * The old leader becomes a thread of the this thread group.
		 * Note: The old leader also uses this pid until release_task
		 *       is called.  Odd but simple and correct.
		 */
		tsk->pid = leader->pid;
		change_pid(tsk, PIDTYPE_PID, task_pid(leader));
		transfer_pid(leader, tsk, PIDTYPE_TGID);
		transfer_pid(leader, tsk, PIDTYPE_PGID);
		transfer_pid(leader, tsk, PIDTYPE_SID);

		list_replace_rcu(&leader->tasks, &tsk->tasks);
		list_replace_init(&leader->sibling, &tsk->sibling);

		tsk->group_leader = tsk;
		leader->group_leader = tsk;

		tsk->exit_signal = SIGCHLD;
		leader->exit_signal = -1;

		BUG_ON(leader->exit_state != EXIT_ZOMBIE);
		leader->exit_state = EXIT_DEAD;

		/*
		 * We are going to release_task()->ptrace_unlink() silently,
		 * the tracer can sleep in do_wait(). EXIT_DEAD guarantees
		 * the tracer wont't block again waiting for this thread.
		 */
		if (unlikely(leader->ptrace))
			__wake_up_parent(leader, leader->parent);
		write_unlock_irq(&tasklist_lock);
		cgroup_threadgroup_change_end(tsk);

		release_task(leader);
	}

	sig->group_exit_task = NULL;
	sig->notify_count = 0;

no_thread_group:
	/* we have changed execution domain */
	tsk->exit_signal = SIGCHLD;

#ifdef CONFIG_POSIX_TIMERS
	exit_itimers(sig);
	flush_itimer_signals();
#endif

	if (refcount_read(&oldsighand->count) != 1) {
		struct sighand_struct *newsighand;
		/*
		 * This ->sighand is shared with the CLONE_SIGHAND
		 * but not CLONE_THREAD task, switch to the new one.
		 */
		newsighand = kmem_cache_alloc(sighand_cachep, GFP_KERNEL);
		if (!newsighand)
			return -ENOMEM;

		refcount_set(&newsighand->count, 1);
		memcpy(newsighand->action, oldsighand->action,
		       sizeof(newsighand->action));

		write_lock_irq(&tasklist_lock);
		spin_lock(&oldsighand->siglock);
		rcu_assign_pointer(tsk->sighand, newsighand);
		spin_unlock(&oldsighand->siglock);
		write_unlock_irq(&tasklist_lock);

		__cleanup_sighand(oldsighand);
	}

	BUG_ON(!thread_group_leader(tsk));
	return 0;

killed:
	/* protects against exit_notify() and __exit_signal() */
	read_lock(&tasklist_lock);
	sig->group_exit_task = NULL;
	sig->notify_count = 0;
	read_unlock(&tasklist_lock);
	return -EAGAIN;
}