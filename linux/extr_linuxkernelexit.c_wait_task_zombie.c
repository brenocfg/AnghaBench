#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  scalar_t__ u64 ;
struct waitid_info {int status; int pid; int /*<<< orphan*/  uid; int /*<<< orphan*/  cause; } ;
struct wait_opts {int wo_flags; int wo_stat; struct waitid_info* wo_info; scalar_t__ wo_rusage; } ;
struct task_struct {int exit_code; int exit_state; int /*<<< orphan*/  exit_signal; struct signal_struct* signal; int /*<<< orphan*/  ioac; scalar_t__ nivcsw; scalar_t__ nvcsw; scalar_t__ maj_flt; scalar_t__ min_flt; } ;
struct signal_struct {unsigned long cmaxrss; int flags; int group_exit_code; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  ioac; int /*<<< orphan*/  maxrss; scalar_t__ coublock; scalar_t__ oublock; scalar_t__ cinblock; scalar_t__ inblock; scalar_t__ cnivcsw; scalar_t__ nivcsw; scalar_t__ cnvcsw; scalar_t__ nvcsw; scalar_t__ cmaj_flt; scalar_t__ maj_flt; scalar_t__ cmin_flt; scalar_t__ min_flt; scalar_t__ cgtime; scalar_t__ gtime; scalar_t__ cstime; scalar_t__ cutime; } ;
typedef  int pid_t ;
struct TYPE_4__ {TYPE_1__* sighand; struct signal_struct* signal; } ;
struct TYPE_3__ {int /*<<< orphan*/  siglock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLD_DUMPED ; 
 int /*<<< orphan*/  CLD_EXITED ; 
 int /*<<< orphan*/  CLD_KILLED ; 
 int EXIT_DEAD ; 
 int EXIT_TRACE ; 
 int EXIT_ZOMBIE ; 
 int /*<<< orphan*/  RUSAGE_BOTH ; 
 int SIGNAL_GROUP_EXIT ; 
 int WEXITED ; 
 int WNOWAIT ; 
 int cmpxchg (int*,int,int) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  current_user_ns () ; 
 scalar_t__ do_notify_parent (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  getrusage (struct task_struct*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  likely (int) ; 
 unsigned long max (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ ptrace_reparented (struct task_struct*) ; 
 int /*<<< orphan*/  ptrace_unlink (struct task_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_task (struct task_struct*) ; 
 int /*<<< orphan*/  sched_annotate_sleep () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ task_gtime (struct task_struct*) ; 
 int /*<<< orphan*/  task_io_accounting_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ task_io_get_inblock (struct task_struct*) ; 
 scalar_t__ task_io_get_oublock (struct task_struct*) ; 
 int task_pid_vnr (struct task_struct*) ; 
 int /*<<< orphan*/  task_uid (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  thread_group_cputime_adjusted (struct task_struct*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ thread_group_leader (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wait_task_zombie(struct wait_opts *wo, struct task_struct *p)
{
	int state, status;
	pid_t pid = task_pid_vnr(p);
	uid_t uid = from_kuid_munged(current_user_ns(), task_uid(p));
	struct waitid_info *infop;

	if (!likely(wo->wo_flags & WEXITED))
		return 0;

	if (unlikely(wo->wo_flags & WNOWAIT)) {
		status = p->exit_code;
		get_task_struct(p);
		read_unlock(&tasklist_lock);
		sched_annotate_sleep();
		if (wo->wo_rusage)
			getrusage(p, RUSAGE_BOTH, wo->wo_rusage);
		put_task_struct(p);
		goto out_info;
	}
	/*
	 * Move the task's state to DEAD/TRACE, only one thread can do this.
	 */
	state = (ptrace_reparented(p) && thread_group_leader(p)) ?
		EXIT_TRACE : EXIT_DEAD;
	if (cmpxchg(&p->exit_state, EXIT_ZOMBIE, state) != EXIT_ZOMBIE)
		return 0;
	/*
	 * We own this thread, nobody else can reap it.
	 */
	read_unlock(&tasklist_lock);
	sched_annotate_sleep();

	/*
	 * Check thread_group_leader() to exclude the traced sub-threads.
	 */
	if (state == EXIT_DEAD && thread_group_leader(p)) {
		struct signal_struct *sig = p->signal;
		struct signal_struct *psig = current->signal;
		unsigned long maxrss;
		u64 tgutime, tgstime;

		/*
		 * The resource counters for the group leader are in its
		 * own task_struct.  Those for dead threads in the group
		 * are in its signal_struct, as are those for the child
		 * processes it has previously reaped.  All these
		 * accumulate in the parent's signal_struct c* fields.
		 *
		 * We don't bother to take a lock here to protect these
		 * p->signal fields because the whole thread group is dead
		 * and nobody can change them.
		 *
		 * psig->stats_lock also protects us from our sub-theads
		 * which can reap other children at the same time. Until
		 * we change k_getrusage()-like users to rely on this lock
		 * we have to take ->siglock as well.
		 *
		 * We use thread_group_cputime_adjusted() to get times for
		 * the thread group, which consolidates times for all threads
		 * in the group including the group leader.
		 */
		thread_group_cputime_adjusted(p, &tgutime, &tgstime);
		spin_lock_irq(&current->sighand->siglock);
		write_seqlock(&psig->stats_lock);
		psig->cutime += tgutime + sig->cutime;
		psig->cstime += tgstime + sig->cstime;
		psig->cgtime += task_gtime(p) + sig->gtime + sig->cgtime;
		psig->cmin_flt +=
			p->min_flt + sig->min_flt + sig->cmin_flt;
		psig->cmaj_flt +=
			p->maj_flt + sig->maj_flt + sig->cmaj_flt;
		psig->cnvcsw +=
			p->nvcsw + sig->nvcsw + sig->cnvcsw;
		psig->cnivcsw +=
			p->nivcsw + sig->nivcsw + sig->cnivcsw;
		psig->cinblock +=
			task_io_get_inblock(p) +
			sig->inblock + sig->cinblock;
		psig->coublock +=
			task_io_get_oublock(p) +
			sig->oublock + sig->coublock;
		maxrss = max(sig->maxrss, sig->cmaxrss);
		if (psig->cmaxrss < maxrss)
			psig->cmaxrss = maxrss;
		task_io_accounting_add(&psig->ioac, &p->ioac);
		task_io_accounting_add(&psig->ioac, &sig->ioac);
		write_sequnlock(&psig->stats_lock);
		spin_unlock_irq(&current->sighand->siglock);
	}

	if (wo->wo_rusage)
		getrusage(p, RUSAGE_BOTH, wo->wo_rusage);
	status = (p->signal->flags & SIGNAL_GROUP_EXIT)
		? p->signal->group_exit_code : p->exit_code;
	wo->wo_stat = status;

	if (state == EXIT_TRACE) {
		write_lock_irq(&tasklist_lock);
		/* We dropped tasklist, ptracer could die and untrace */
		ptrace_unlink(p);

		/* If parent wants a zombie, don't release it now */
		state = EXIT_ZOMBIE;
		if (do_notify_parent(p, p->exit_signal))
			state = EXIT_DEAD;
		p->exit_state = state;
		write_unlock_irq(&tasklist_lock);
	}
	if (state == EXIT_DEAD)
		release_task(p);

out_info:
	infop = wo->wo_info;
	if (infop) {
		if ((status & 0x7f) == 0) {
			infop->cause = CLD_EXITED;
			infop->status = status >> 8;
		} else {
			infop->cause = (status & 0x80) ? CLD_DUMPED : CLD_KILLED;
			infop->status = status & 0x7f;
		}
		infop->pid = pid;
		infop->uid = uid;
	}

	return pid;
}