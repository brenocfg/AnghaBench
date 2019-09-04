#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct kernfs_open_file {int /*<<< orphan*/  kn; TYPE_3__* file; } ;
struct cgroup {int dummy; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct TYPE_6__ {TYPE_2__ f_path; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 size_t ENODEV ; 
 size_t PTR_ERR_OR_ZERO (struct task_struct*) ; 
 size_t cgroup_attach_task (struct cgroup*,struct task_struct*,int) ; 
 struct cgroup* cgroup_kn_lock_live (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cgroup_kn_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_procs_write_finish (struct task_struct*) ; 
 size_t cgroup_procs_write_permission (struct cgroup*,struct cgroup*,int /*<<< orphan*/ ) ; 
 struct task_struct* cgroup_procs_write_start (char*,int) ; 
 int /*<<< orphan*/  cgrp_dfl_root ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct cgroup* task_cgroup_from_root (struct task_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t cgroup_procs_write(struct kernfs_open_file *of,
				  char *buf, size_t nbytes, loff_t off)
{
	struct cgroup *src_cgrp, *dst_cgrp;
	struct task_struct *task;
	ssize_t ret;

	dst_cgrp = cgroup_kn_lock_live(of->kn, false);
	if (!dst_cgrp)
		return -ENODEV;

	task = cgroup_procs_write_start(buf, true);
	ret = PTR_ERR_OR_ZERO(task);
	if (ret)
		goto out_unlock;

	/* find the source cgroup */
	spin_lock_irq(&css_set_lock);
	src_cgrp = task_cgroup_from_root(task, &cgrp_dfl_root);
	spin_unlock_irq(&css_set_lock);

	ret = cgroup_procs_write_permission(src_cgrp, dst_cgrp,
					    of->file->f_path.dentry->d_sb);
	if (ret)
		goto out_finish;

	ret = cgroup_attach_task(dst_cgrp, task, true);

out_finish:
	cgroup_procs_write_finish(task);
out_unlock:
	cgroup_kn_unlock(of->kn);

	return ret ?: nbytes;
}