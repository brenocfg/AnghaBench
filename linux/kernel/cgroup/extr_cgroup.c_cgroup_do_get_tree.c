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
struct super_block {int dummy; } ;
struct fs_context {struct dentry* root; int /*<<< orphan*/ * fs_type; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  new_sb_created; int /*<<< orphan*/  magic; int /*<<< orphan*/  root; } ;
struct cgroup_fs_context {TYPE_3__* root; TYPE_1__ kfc; TYPE_2__* ns; } ;
struct cgroup {int /*<<< orphan*/  kn; } ;
struct TYPE_6__ {int /*<<< orphan*/  cgrp; int /*<<< orphan*/  kf_root; } ;
struct TYPE_5__ {int /*<<< orphan*/  root_cset; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGROUP2_SUPER_MAGIC ; 
 int /*<<< orphan*/  CGROUP_SUPER_MAGIC ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  cgroup2_fs_type ; 
 struct cgroup_fs_context* cgroup_fc2context (struct fs_context*) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  cgroup_put (int /*<<< orphan*/ *) ; 
 struct cgroup* cset_cgroup_from_root (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 TYPE_2__ init_cgroup_ns ; 
 int kernfs_get_tree (struct fs_context*) ; 
 struct dentry* kernfs_node_dentry (int /*<<< orphan*/ ,struct super_block*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int cgroup_do_get_tree(struct fs_context *fc)
{
	struct cgroup_fs_context *ctx = cgroup_fc2context(fc);
	int ret;

	ctx->kfc.root = ctx->root->kf_root;
	if (fc->fs_type == &cgroup2_fs_type)
		ctx->kfc.magic = CGROUP2_SUPER_MAGIC;
	else
		ctx->kfc.magic = CGROUP_SUPER_MAGIC;
	ret = kernfs_get_tree(fc);

	/*
	 * In non-init cgroup namespace, instead of root cgroup's dentry,
	 * we return the dentry corresponding to the cgroupns->root_cgrp.
	 */
	if (!ret && ctx->ns != &init_cgroup_ns) {
		struct dentry *nsdentry;
		struct super_block *sb = fc->root->d_sb;
		struct cgroup *cgrp;

		mutex_lock(&cgroup_mutex);
		spin_lock_irq(&css_set_lock);

		cgrp = cset_cgroup_from_root(ctx->ns->root_cset, ctx->root);

		spin_unlock_irq(&css_set_lock);
		mutex_unlock(&cgroup_mutex);

		nsdentry = kernfs_node_dentry(cgrp->kn, sb);
		dput(fc->root);
		fc->root = nsdentry;
		if (IS_ERR(nsdentry)) {
			ret = PTR_ERR(nsdentry);
			deactivate_locked_super(sb);
		}
	}

	if (!ctx->kfc.new_sb_created)
		cgroup_put(&ctx->root->cgrp);

	return ret;
}