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
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {int dummy; } ;
struct pid_namespace {int dummy; } ;
struct path {int /*<<< orphan*/  dentry; } ;
struct kstat {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int /*<<< orphan*/  HIDEPID_INVISIBLE ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 
 int /*<<< orphan*/  has_pid_permissions (struct pid_namespace*,struct task_struct*,int /*<<< orphan*/ ) ; 
 struct task_struct* pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_pid (struct inode*) ; 
 struct pid_namespace* proc_pid_ns (struct inode*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  task_dump_owner (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int pid_getattr(const struct path *path, struct kstat *stat,
		u32 request_mask, unsigned int query_flags)
{
	struct inode *inode = d_inode(path->dentry);
	struct pid_namespace *pid = proc_pid_ns(inode);
	struct task_struct *task;

	generic_fillattr(inode, stat);

	stat->uid = GLOBAL_ROOT_UID;
	stat->gid = GLOBAL_ROOT_GID;
	rcu_read_lock();
	task = pid_task(proc_pid(inode), PIDTYPE_PID);
	if (task) {
		if (!has_pid_permissions(pid, task, HIDEPID_INVISIBLE)) {
			rcu_read_unlock();
			/*
			 * This doesn't prevent learning whether PID exists,
			 * it only makes getattr() consistent with readdir().
			 */
			return -ENOENT;
		}
		task_dump_owner(task, inode->i_mode, &stat->uid, &stat->gid);
	}
	rcu_read_unlock();
	return 0;
}