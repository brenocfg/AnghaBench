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
struct task_struct {int /*<<< orphan*/  timer_slack_ns; } ;
struct seq_file {struct inode* private; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_NICE ; 
 int EPERM ; 
 int ESRCH ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int security_task_getscheduler (struct task_struct*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

__attribute__((used)) static int timerslack_ns_show(struct seq_file *m, void *v)
{
	struct inode *inode = m->private;
	struct task_struct *p;
	int err = 0;

	p = get_proc_task(inode);
	if (!p)
		return -ESRCH;

	if (p != current) {

		if (!capable(CAP_SYS_NICE)) {
			err = -EPERM;
			goto out;
		}
		err = security_task_getscheduler(p);
		if (err)
			goto out;
	}

	task_lock(p);
	seq_printf(m, "%llu\n", p->timer_slack_ns);
	task_unlock(p);

out:
	put_task_struct(p);

	return err;
}