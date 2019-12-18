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
struct task_struct {int dummy; } ;
struct kernfs_open_file {int /*<<< orphan*/  kn; } ;
struct cred {int /*<<< orphan*/  suid; int /*<<< orphan*/  euid; int /*<<< orphan*/  uid; } ;
struct cgroup {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int EACCES ; 
 int ENODEV ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int PTR_ERR_OR_ZERO (struct task_struct*) ; 
 int cgroup_attach_task (struct cgroup*,struct task_struct*,int) ; 
 struct cgroup* cgroup_kn_lock_live (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cgroup_kn_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_procs_write_finish (struct task_struct*) ; 
 struct task_struct* cgroup_procs_write_start (char*,int) ; 
 struct cred* current_cred () ; 
 struct cred* get_task_cred (struct task_struct*) ; 
 int /*<<< orphan*/  put_cred (struct cred const*) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t __cgroup1_procs_write(struct kernfs_open_file *of,
				     char *buf, size_t nbytes, loff_t off,
				     bool threadgroup)
{
	struct cgroup *cgrp;
	struct task_struct *task;
	const struct cred *cred, *tcred;
	ssize_t ret;

	cgrp = cgroup_kn_lock_live(of->kn, false);
	if (!cgrp)
		return -ENODEV;

	task = cgroup_procs_write_start(buf, threadgroup);
	ret = PTR_ERR_OR_ZERO(task);
	if (ret)
		goto out_unlock;

	/*
	 * Even if we're attaching all tasks in the thread group, we only
	 * need to check permissions on one of them.
	 */
	cred = current_cred();
	tcred = get_task_cred(task);
	if (!uid_eq(cred->euid, GLOBAL_ROOT_UID) &&
	    !uid_eq(cred->euid, tcred->uid) &&
	    !uid_eq(cred->euid, tcred->suid))
		ret = -EACCES;
	put_cred(tcred);
	if (ret)
		goto out_finish;

	ret = cgroup_attach_task(cgrp, task, threadgroup);

out_finish:
	cgroup_procs_write_finish(task);
out_unlock:
	cgroup_kn_unlock(of->kn);

	return ret ?: nbytes;
}