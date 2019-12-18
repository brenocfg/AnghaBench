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
struct upid {int /*<<< orphan*/  nr; struct pid_namespace* ns; } ;
struct pid_namespace {int pid_allocated; int /*<<< orphan*/  idr; int /*<<< orphan*/  proc_work; int /*<<< orphan*/  child_reaper; } ;
struct pid {int level; int /*<<< orphan*/  rcu; struct upid* numbers; } ;

/* Variables and functions */
#define  PIDNS_ADDING 128 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delayed_put_pid ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pidmap_lock ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void free_pid(struct pid *pid)
{
	/* We can be called with write_lock_irq(&tasklist_lock) held */
	int i;
	unsigned long flags;

	spin_lock_irqsave(&pidmap_lock, flags);
	for (i = 0; i <= pid->level; i++) {
		struct upid *upid = pid->numbers + i;
		struct pid_namespace *ns = upid->ns;
		switch (--ns->pid_allocated) {
		case 2:
		case 1:
			/* When all that is left in the pid namespace
			 * is the reaper wake up the reaper.  The reaper
			 * may be sleeping in zap_pid_ns_processes().
			 */
			wake_up_process(ns->child_reaper);
			break;
		case PIDNS_ADDING:
			/* Handle a fork failure of the first process */
			WARN_ON(ns->child_reaper);
			ns->pid_allocated = 0;
			/* fall through */
		case 0:
			schedule_work(&ns->proc_work);
			break;
		}

		idr_remove(&ns->idr, upid->nr);
	}
	spin_unlock_irqrestore(&pidmap_lock, flags);

	call_rcu(&pid->rcu, delayed_put_pid);
}