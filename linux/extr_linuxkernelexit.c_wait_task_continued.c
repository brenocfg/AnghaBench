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
struct waitid_info {int pid; int /*<<< orphan*/  status; int /*<<< orphan*/  uid; int /*<<< orphan*/  cause; } ;
struct wait_opts {int wo_flags; int wo_stat; struct waitid_info* wo_info; scalar_t__ wo_rusage; } ;
struct task_struct {TYPE_2__* sighand; TYPE_1__* signal; } ;
typedef  int pid_t ;
struct TYPE_4__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLD_CONTINUED ; 
 int /*<<< orphan*/  RUSAGE_BOTH ; 
 int /*<<< orphan*/  SIGCONT ; 
 int SIGNAL_STOP_CONTINUED ; 
 int WCONTINUED ; 
 int WNOWAIT ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  getrusage (struct task_struct*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_annotate_sleep () ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int task_pid_vnr (struct task_struct*) ; 
 int /*<<< orphan*/  task_uid (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  unlikely (int) ; 

__attribute__((used)) static int wait_task_continued(struct wait_opts *wo, struct task_struct *p)
{
	struct waitid_info *infop;
	pid_t pid;
	uid_t uid;

	if (!unlikely(wo->wo_flags & WCONTINUED))
		return 0;

	if (!(p->signal->flags & SIGNAL_STOP_CONTINUED))
		return 0;

	spin_lock_irq(&p->sighand->siglock);
	/* Re-check with the lock held.  */
	if (!(p->signal->flags & SIGNAL_STOP_CONTINUED)) {
		spin_unlock_irq(&p->sighand->siglock);
		return 0;
	}
	if (!unlikely(wo->wo_flags & WNOWAIT))
		p->signal->flags &= ~SIGNAL_STOP_CONTINUED;
	uid = from_kuid_munged(current_user_ns(), task_uid(p));
	spin_unlock_irq(&p->sighand->siglock);

	pid = task_pid_vnr(p);
	get_task_struct(p);
	read_unlock(&tasklist_lock);
	sched_annotate_sleep();
	if (wo->wo_rusage)
		getrusage(p, RUSAGE_BOTH, wo->wo_rusage);
	put_task_struct(p);

	infop = wo->wo_info;
	if (!infop) {
		wo->wo_stat = 0xffff;
	} else {
		infop->cause = CLD_CONTINUED;
		infop->pid = pid;
		infop->uid = uid;
		infop->status = SIGCONT;
	}
	return pid;
}