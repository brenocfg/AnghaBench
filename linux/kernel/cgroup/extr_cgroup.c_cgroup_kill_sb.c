#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct kernfs_root {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  children; } ;
struct TYPE_4__ {TYPE_1__ self; } ;
struct cgroup_root {TYPE_2__ cgrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_put (TYPE_2__*) ; 
 struct cgroup_root* cgroup_root_from_kf (struct kernfs_root*) ; 
 struct cgroup_root cgrp_dfl_root ; 
 int /*<<< orphan*/  kernfs_kill_sb (struct super_block*) ; 
 struct kernfs_root* kernfs_root_from_sb (struct super_block*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_is_dying (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cgroup_kill_sb(struct super_block *sb)
{
	struct kernfs_root *kf_root = kernfs_root_from_sb(sb);
	struct cgroup_root *root = cgroup_root_from_kf(kf_root);

	/*
	 * If @root doesn't have any children, start killing it.
	 * This prevents new mounts by disabling percpu_ref_tryget_live().
	 * cgroup_mount() may wait for @root's release.
	 *
	 * And don't kill the default root.
	 */
	if (list_empty(&root->cgrp.self.children) && root != &cgrp_dfl_root &&
	    !percpu_ref_is_dying(&root->cgrp.self.refcnt))
		percpu_ref_kill(&root->cgrp.self.refcnt);
	cgroup_put(&root->cgrp);
	kernfs_kill_sb(sb);
}