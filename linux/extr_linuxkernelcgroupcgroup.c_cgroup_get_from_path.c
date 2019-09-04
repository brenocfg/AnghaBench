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
struct kernfs_node {struct cgroup* priv; } ;
struct cgroup {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  kn; } ;
struct TYPE_4__ {TYPE_1__ cgrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOTDIR ; 
 struct cgroup* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ KERNFS_DIR ; 
 int /*<<< orphan*/  cgroup_get_live (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 TYPE_2__ cgrp_dfl_root ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 scalar_t__ kernfs_type (struct kernfs_node*) ; 
 struct kernfs_node* kernfs_walk_and_get (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct cgroup *cgroup_get_from_path(const char *path)
{
	struct kernfs_node *kn;
	struct cgroup *cgrp;

	mutex_lock(&cgroup_mutex);

	kn = kernfs_walk_and_get(cgrp_dfl_root.cgrp.kn, path);
	if (kn) {
		if (kernfs_type(kn) == KERNFS_DIR) {
			cgrp = kn->priv;
			cgroup_get_live(cgrp);
		} else {
			cgrp = ERR_PTR(-ENOTDIR);
		}
		kernfs_put(kn);
	} else {
		cgrp = ERR_PTR(-ENOENT);
	}

	mutex_unlock(&cgroup_mutex);
	return cgrp;
}