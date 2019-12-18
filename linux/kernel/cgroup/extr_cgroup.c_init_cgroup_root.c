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
struct cgroup {int /*<<< orphan*/  flags; struct cgroup_root* root; } ;
struct cgroup_root {struct cgroup cgrp; int /*<<< orphan*/  name; int /*<<< orphan*/  release_agent_path; int /*<<< orphan*/  flags; int /*<<< orphan*/  cgroup_idr; int /*<<< orphan*/  nr_cgrps; int /*<<< orphan*/  root_list; } ;
struct cgroup_fs_context {scalar_t__ cpuset_clone_children; int /*<<< orphan*/  name; int /*<<< orphan*/  release_agent; int /*<<< orphan*/  flags; struct cgroup_root* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGRP_CPUSET_CLONE_CHILDREN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_CGROUP_ROOT_NAMELEN ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_cgroup_housekeeping (struct cgroup*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void init_cgroup_root(struct cgroup_fs_context *ctx)
{
	struct cgroup_root *root = ctx->root;
	struct cgroup *cgrp = &root->cgrp;

	INIT_LIST_HEAD(&root->root_list);
	atomic_set(&root->nr_cgrps, 1);
	cgrp->root = root;
	init_cgroup_housekeeping(cgrp);
	idr_init(&root->cgroup_idr);

	root->flags = ctx->flags;
	if (ctx->release_agent)
		strscpy(root->release_agent_path, ctx->release_agent, PATH_MAX);
	if (ctx->name)
		strscpy(root->name, ctx->name, MAX_CGROUP_ROOT_NAMELEN);
	if (ctx->cpuset_clone_children)
		set_bit(CGRP_CPUSET_CLONE_CHILDREN, &root->cgrp.flags);
}