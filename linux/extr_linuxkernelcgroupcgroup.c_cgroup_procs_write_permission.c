#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {int dummy; } ;
struct cgroup_namespace {TYPE_2__* root_cset; } ;
struct TYPE_6__ {int /*<<< orphan*/  kn; } ;
struct cgroup {TYPE_1__ procs_file; } ;
struct TYPE_10__ {int flags; } ;
struct TYPE_9__ {TYPE_3__* nsproxy; } ;
struct TYPE_8__ {struct cgroup_namespace* cgroup_ns; } ;
struct TYPE_7__ {struct cgroup* dfl_cgrp; } ;

/* Variables and functions */
 int CGRP_ROOT_NS_DELEGATE ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int /*<<< orphan*/  cgroup_is_descendant (struct cgroup*,struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 struct cgroup* cgroup_parent (struct cgroup*) ; 
 TYPE_5__ cgrp_dfl_root ; 
 TYPE_4__* current ; 
 int inode_permission (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* kernfs_get_inode (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cgroup_procs_write_permission(struct cgroup *src_cgrp,
					 struct cgroup *dst_cgrp,
					 struct super_block *sb)
{
	struct cgroup_namespace *ns = current->nsproxy->cgroup_ns;
	struct cgroup *com_cgrp = src_cgrp;
	struct inode *inode;
	int ret;

	lockdep_assert_held(&cgroup_mutex);

	/* find the common ancestor */
	while (!cgroup_is_descendant(dst_cgrp, com_cgrp))
		com_cgrp = cgroup_parent(com_cgrp);

	/* %current should be authorized to migrate to the common ancestor */
	inode = kernfs_get_inode(sb, com_cgrp->procs_file.kn);
	if (!inode)
		return -ENOMEM;

	ret = inode_permission(inode, MAY_WRITE);
	iput(inode);
	if (ret)
		return ret;

	/*
	 * If namespaces are delegation boundaries, %current must be able
	 * to see both source and destination cgroups from its namespace.
	 */
	if ((cgrp_dfl_root.flags & CGRP_ROOT_NS_DELEGATE) &&
	    (!cgroup_is_descendant(src_cgrp, ns->root_cset->dfl_cgrp) ||
	     !cgroup_is_descendant(dst_cgrp, ns->root_cset->dfl_cgrp)))
		return -ENOENT;

	return 0;
}