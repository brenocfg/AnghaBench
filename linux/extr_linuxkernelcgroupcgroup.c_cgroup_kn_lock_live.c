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
struct kernfs_node {TYPE_1__* parent; struct cgroup* priv; } ;
struct cgroup {int dummy; } ;
struct TYPE_2__ {struct cgroup* priv; } ;

/* Variables and functions */
 scalar_t__ KERNFS_DIR ; 
 int /*<<< orphan*/  cgroup_is_dead (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_kn_unlock (struct kernfs_node*) ; 
 int /*<<< orphan*/  cgroup_lock_and_drain_offline (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  cgroup_tryget (struct cgroup*) ; 
 int /*<<< orphan*/  kernfs_break_active_protection (struct kernfs_node*) ; 
 scalar_t__ kernfs_type (struct kernfs_node*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

struct cgroup *cgroup_kn_lock_live(struct kernfs_node *kn, bool drain_offline)
{
	struct cgroup *cgrp;

	if (kernfs_type(kn) == KERNFS_DIR)
		cgrp = kn->priv;
	else
		cgrp = kn->parent->priv;

	/*
	 * We're gonna grab cgroup_mutex which nests outside kernfs
	 * active_ref.  cgroup liveliness check alone provides enough
	 * protection against removal.  Ensure @cgrp stays accessible and
	 * break the active_ref protection.
	 */
	if (!cgroup_tryget(cgrp))
		return NULL;
	kernfs_break_active_protection(kn);

	if (drain_offline)
		cgroup_lock_and_drain_offline(cgrp);
	else
		mutex_lock(&cgroup_mutex);

	if (!cgroup_is_dead(cgrp))
		return cgrp;

	cgroup_kn_unlock(kn);
	return NULL;
}