#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct kernfs_root {int dummy; } ;
struct fs_context {TYPE_1__* root; } ;
struct TYPE_7__ {int /*<<< orphan*/  children; } ;
struct TYPE_9__ {TYPE_2__ self; } ;
struct cgroup_root {int subsys_mask; int flags; int /*<<< orphan*/  release_agent_path; TYPE_5__ cgrp; int /*<<< orphan*/  name; } ;
struct cgroup_fs_context {int subsys_mask; int flags; scalar_t__ release_agent; scalar_t__ name; } ;
struct TYPE_8__ {int /*<<< orphan*/  comm; } ;
struct TYPE_6__ {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cg_invalf (struct fs_context*,char*,int,char*,int,int /*<<< orphan*/ ) ; 
 struct cgroup_fs_context* cgroup_fc2context (struct fs_context*) ; 
 int /*<<< orphan*/  cgroup_lock_and_drain_offline (TYPE_5__*) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 struct cgroup_root* cgroup_root_from_kf (struct kernfs_root*) ; 
 struct cgroup_root cgrp_dfl_root ; 
 int check_cgroupfs_options (struct fs_context*) ; 
 TYPE_3__* current ; 
 struct kernfs_root* kernfs_root_from_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rebind_subsystems (struct cgroup_root*,int) ; 
 int /*<<< orphan*/  release_agent_path_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  task_tgid_nr (TYPE_3__*) ; 
 int /*<<< orphan*/  trace_cgroup_remount (struct cgroup_root*) ; 

int cgroup1_reconfigure(struct fs_context *fc)
{
	struct cgroup_fs_context *ctx = cgroup_fc2context(fc);
	struct kernfs_root *kf_root = kernfs_root_from_sb(fc->root->d_sb);
	struct cgroup_root *root = cgroup_root_from_kf(kf_root);
	int ret = 0;
	u16 added_mask, removed_mask;

	cgroup_lock_and_drain_offline(&cgrp_dfl_root.cgrp);

	/* See what subsystems are wanted */
	ret = check_cgroupfs_options(fc);
	if (ret)
		goto out_unlock;

	if (ctx->subsys_mask != root->subsys_mask || ctx->release_agent)
		pr_warn("option changes via remount are deprecated (pid=%d comm=%s)\n",
			task_tgid_nr(current), current->comm);

	added_mask = ctx->subsys_mask & ~root->subsys_mask;
	removed_mask = root->subsys_mask & ~ctx->subsys_mask;

	/* Don't allow flags or name to change at remount */
	if ((ctx->flags ^ root->flags) ||
	    (ctx->name && strcmp(ctx->name, root->name))) {
		cg_invalf(fc, "option or name mismatch, new: 0x%x \"%s\", old: 0x%x \"%s\"",
		       ctx->flags, ctx->name ?: "", root->flags, root->name);
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

	if (ctx->release_agent) {
		spin_lock(&release_agent_path_lock);
		strcpy(root->release_agent_path, ctx->release_agent);
		spin_unlock(&release_agent_path_lock);
	}

	trace_cgroup_remount(root);

 out_unlock:
	mutex_unlock(&cgroup_mutex);
	return ret;
}