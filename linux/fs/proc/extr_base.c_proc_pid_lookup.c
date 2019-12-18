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
struct task_struct {int dummy; } ;
struct pid_namespace {int dummy; } ;
struct dentry {TYPE_1__* d_sb; int /*<<< orphan*/  d_name; } ;
struct TYPE_2__ {struct pid_namespace* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct task_struct* find_task_by_pid_ns (unsigned int,struct pid_namespace*) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 unsigned int name_to_int (int /*<<< orphan*/ *) ; 
 struct dentry* proc_pid_instantiate (struct dentry*,struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct dentry *proc_pid_lookup(struct dentry *dentry, unsigned int flags)
{
	struct task_struct *task;
	unsigned tgid;
	struct pid_namespace *ns;
	struct dentry *result = ERR_PTR(-ENOENT);

	tgid = name_to_int(&dentry->d_name);
	if (tgid == ~0U)
		goto out;

	ns = dentry->d_sb->s_fs_info;
	rcu_read_lock();
	task = find_task_by_pid_ns(tgid, ns);
	if (task)
		get_task_struct(task);
	rcu_read_unlock();
	if (!task)
		goto out;

	result = proc_pid_instantiate(dentry, task, NULL);
	put_task_struct(task);
out:
	return result;
}