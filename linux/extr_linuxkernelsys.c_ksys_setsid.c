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
struct task_struct {TYPE_1__* signal; } ;
struct pid {int dummy; } ;
typedef  int pid_t ;
struct TYPE_4__ {struct task_struct* group_leader; } ;
struct TYPE_3__ {int leader; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  PIDTYPE_PGID ; 
 TYPE_2__* current ; 
 scalar_t__ pid_task (struct pid*,int /*<<< orphan*/ ) ; 
 int pid_vnr (struct pid*) ; 
 int /*<<< orphan*/  proc_clear_tty (struct task_struct*) ; 
 int /*<<< orphan*/  proc_sid_connector (struct task_struct*) ; 
 int /*<<< orphan*/  sched_autogroup_create_attach (struct task_struct*) ; 
 int /*<<< orphan*/  set_special_pids (struct pid*) ; 
 struct pid* task_pid (struct task_struct*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  write_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_irq (int /*<<< orphan*/ *) ; 

int ksys_setsid(void)
{
	struct task_struct *group_leader = current->group_leader;
	struct pid *sid = task_pid(group_leader);
	pid_t session = pid_vnr(sid);
	int err = -EPERM;

	write_lock_irq(&tasklist_lock);
	/* Fail if I am already a session leader */
	if (group_leader->signal->leader)
		goto out;

	/* Fail if a process group id already exists that equals the
	 * proposed session id.
	 */
	if (pid_task(sid, PIDTYPE_PGID))
		goto out;

	group_leader->signal->leader = 1;
	set_special_pids(sid);

	proc_clear_tty(group_leader);

	err = session;
out:
	write_unlock_irq(&tasklist_lock);
	if (err > 0) {
		proc_sid_connector(group_leader);
		sched_autogroup_create_attach(group_leader);
	}
	return err;
}