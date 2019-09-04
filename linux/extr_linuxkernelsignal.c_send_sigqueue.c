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
struct sigpending {int /*<<< orphan*/  signal; int /*<<< orphan*/  list; } ;
struct task_struct {struct sigpending pending; TYPE_1__* signal; } ;
struct TYPE_4__ {int si_signo; scalar_t__ si_code; scalar_t__ si_overrun; } ;
struct sigqueue {int flags; TYPE_2__ info; int /*<<< orphan*/  list; } ;
struct pid {int dummy; } ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;
struct TYPE_3__ {struct sigpending shared_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int PIDTYPE_PID ; 
 int SIGQUEUE_PREALLOC ; 
 scalar_t__ SI_TIMER ; 
 int TRACE_SIGNAL_ALREADY_PENDING ; 
 int TRACE_SIGNAL_DELIVERED ; 
 int TRACE_SIGNAL_IGNORED ; 
 int /*<<< orphan*/  complete_signal (int,struct task_struct*,int) ; 
 int /*<<< orphan*/  likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_task_sighand (struct task_struct*,unsigned long*) ; 
 struct task_struct* pid_task (struct pid*,int) ; 
 int /*<<< orphan*/  prepare_signal (int,struct task_struct*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  signalfd_notify (struct task_struct*,int) ; 
 int /*<<< orphan*/  trace_signal_generate (int,TYPE_2__*,struct task_struct*,int,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 

int send_sigqueue(struct sigqueue *q, struct pid *pid, enum pid_type type)
{
	int sig = q->info.si_signo;
	struct sigpending *pending;
	struct task_struct *t;
	unsigned long flags;
	int ret, result;

	BUG_ON(!(q->flags & SIGQUEUE_PREALLOC));

	ret = -1;
	rcu_read_lock();
	t = pid_task(pid, type);
	if (!t || !likely(lock_task_sighand(t, &flags)))
		goto ret;

	ret = 1; /* the signal is ignored */
	result = TRACE_SIGNAL_IGNORED;
	if (!prepare_signal(sig, t, false))
		goto out;

	ret = 0;
	if (unlikely(!list_empty(&q->list))) {
		/*
		 * If an SI_TIMER entry is already queue just increment
		 * the overrun count.
		 */
		BUG_ON(q->info.si_code != SI_TIMER);
		q->info.si_overrun++;
		result = TRACE_SIGNAL_ALREADY_PENDING;
		goto out;
	}
	q->info.si_overrun = 0;

	signalfd_notify(t, sig);
	pending = (type != PIDTYPE_PID) ? &t->signal->shared_pending : &t->pending;
	list_add_tail(&q->list, &pending->list);
	sigaddset(&pending->signal, sig);
	complete_signal(sig, t, type);
	result = TRACE_SIGNAL_DELIVERED;
out:
	trace_signal_generate(sig, &q->info, t, type != PIDTYPE_PID, result);
	unlock_task_sighand(t, &flags);
ret:
	rcu_read_unlock();
	return ret;
}