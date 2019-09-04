#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct kernfs_root {int dummy; } ;
struct cgroup_sb_opts {int subsys_mask; int flags; scalar_t__ name; scalar_t__ release_agent; } ;
struct TYPE_5__ {int /*<<< orphan*/  children; } ;
struct TYPE_7__ {TYPE_1__ self; } ;
struct cgroup_root {int subsys_mask; int flags; int /*<<< orphan*/  release_agent_path; TYPE_4__ cgrp; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cgroup_lock_and_drain_offline (TYPE_4__*) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 struct cgroup_root* cgroup_root_from_kf (struct kernfs_root*) ; 
 struct cgroup_root cgrp_dfl_root ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int parse_cgroupfs_options (char*,struct cgroup_sb_opts*) ; 
 int /*<<< orphan*/  pr_err (char*,int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rebind_subsystems (struct cgroup_root*,int) ; 
 int /*<<< orphan*/  release_agent_path_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  task_tgid_nr (TYPE_2__*) ; 
 int /*<<< orphan*/  trace_cgroup_remount (struct cgroup_root*) ; 

__attribute__((used)) static int cgroup1_remount(struct kernfs_root *kf_root, int *flags, char *data)
{
	int ret = 0;
	struct cgroup_root *root = cgroup_root_from_kf(kf_root);
	struct cgroup_sb_opts opts;
	u16 added_mask, removed_mask;

	cgroup_lock_and_drain_offline(&cgrp_dfl_root.cgrp);

	/* See what subsystems are wanted */
	ret = parse_cgroupfs_options(data, &opts);
	if (ret)
		goto out_unlock;

	if (opts.subsys_mask != root->subsys_mask || opts.release_agent)
		pr_warn("option changes via remount are deprecated (pid=%d comm=%s)\n",
			task_tgid_nr(current), current->comm);

	added_mask = opts.subsys_mask & ~root->subsys_mask;
	removed_mask = root->subsys_mask & ~opts.subsys_mask;

	/* Don't allow flags or name to change at remount */
	if ((opts.flags ^ root->flags) ||
	    (opts.name && strcmp(opts.name, root->name))) {
		pr_err("option or name mismatch, new: 0x%x \"%s\", old: 0x%x \"%s\"\n",
		       opts.flags, opts.name ?: "", root->flags, root->name);
		ret = -EINVAL;
		goto out_unlock;
	}

	/* remounting is not allowed for populated hierarchies */
	if (!list_empty(&root->cgrp.self.children)) {
		ret = -EBUSY;
		goto out_unlock;
	}

	ret = rebind_subsystems(root, added_mask);
	if (ret)
		goto out_unlock;

	WARN_ON(rebind_subsystems(&cgrp_dfl_root, removed_mask));

	if (opts.release_agent) {
		spin_lock(&release_agent_path_lock);
		strcpy(root->release_agent_path, opts.release_agent);
		spin_unlock(&release_agent_path_lock);
	}

	trace_cgroup_remount(root);

 out_unlock:
	kfree(opts.release_agent);
	kfree(opts.name);
	mutex_unlock(&cgroup_mutex);
	return ret;
}