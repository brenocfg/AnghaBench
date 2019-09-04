#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  signal; } ;
struct task_struct {int /*<<< orphan*/  blocked; TYPE_3__* signal; TYPE_1__ pending; } ;
struct seq_file {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_10__ {TYPE_4__* user; } ;
struct TYPE_9__ {int /*<<< orphan*/  sigpending; } ;
struct TYPE_7__ {int /*<<< orphan*/  signal; } ;
struct TYPE_8__ {TYPE_2__ shared_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_SIGPENDING ; 
 TYPE_5__* __task_cred (struct task_struct*) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  collect_sigign_sigcatch (struct task_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_nr_threads (struct task_struct*) ; 
 scalar_t__ lock_task_sighand (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  render_sigset_t (struct seq_file*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_put_decimal_ull (struct seq_file*,char*,unsigned long) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 unsigned long task_rlimit (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 

__attribute__((used)) static inline void task_sig(struct seq_file *m, struct task_struct *p)
{
	unsigned long flags;
	sigset_t pending, shpending, blocked, ignored, caught;
	int num_threads = 0;
	unsigned int qsize = 0;
	unsigned long qlim = 0;

	sigemptyset(&pending);
	sigemptyset(&shpending);
	sigemptyset(&blocked);
	sigemptyset(&ignored);
	sigemptyset(&caught);

	if (lock_task_sighand(p, &flags)) {
		pending = p->pending.signal;
		shpending = p->signal->shared_pending.signal;
		blocked = p->blocked;
		collect_sigign_sigcatch(p, &ignored, &caught);
		num_threads = get_nr_threads(p);
		rcu_read_lock();  /* FIXME: is this correct? */
		qsize = atomic_read(&__task_cred(p)->user->sigpending);
		rcu_read_unlock();
		qlim = task_rlimit(p, RLIMIT_SIGPENDING);
		unlock_task_sighand(p, &flags);
	}

	seq_put_decimal_ull(m, "Threads:\t", num_threads);
	seq_put_decimal_ull(m, "\nSigQ:\t", qsize);
	seq_put_decimal_ull(m, "/", qlim);

	/* render them all */
	render_sigset_t(m, "\nSigPnd:\t", &pending);
	render_sigset_t(m, "ShdPnd:\t", &shpending);
	render_sigset_t(m, "SigBlk:\t", &blocked);
	render_sigset_t(m, "SigIgn:\t", &ignored);
	render_sigset_t(m, "SigCgt:\t", &caught);
}