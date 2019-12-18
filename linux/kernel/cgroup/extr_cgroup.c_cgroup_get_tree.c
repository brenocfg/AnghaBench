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
struct fs_context {int dummy; } ;
struct cgroup_fs_context {int /*<<< orphan*/  flags; TYPE_1__* root; } ;
struct TYPE_2__ {int /*<<< orphan*/  cgrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  apply_cgroup_root_flags (int /*<<< orphan*/ ) ; 
 int cgroup_do_get_tree (struct fs_context*) ; 
 struct cgroup_fs_context* cgroup_fc2context (struct fs_context*) ; 
 int /*<<< orphan*/  cgroup_get_live (int /*<<< orphan*/ *) ; 
 TYPE_1__ cgrp_dfl_root ; 
 int cgrp_dfl_visible ; 

__attribute__((used)) static int cgroup_get_tree(struct fs_context *fc)
{
	struct cgroup_fs_context *ctx = cgroup_fc2context(fc);
	int ret;

	cgrp_dfl_visible = true;
	cgroup_get_live(&cgrp_dfl_root.cgrp);
	ctx->root = &cgrp_dfl_root;

	ret = cgroup_do_get_tree(fc);
	if (!ret)
		apply_cgroup_root_flags(ctx->flags);
	return ret;
}