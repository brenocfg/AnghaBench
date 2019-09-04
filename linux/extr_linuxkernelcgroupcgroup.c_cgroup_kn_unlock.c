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
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  cgroup_put (struct cgroup*) ; 
 scalar_t__ kernfs_type (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_unbreak_active_protection (struct kernfs_node*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cgroup_kn_unlock(struct kernfs_node *kn)
{
	struct cgroup *cgrp;

	if (kernfs_type(kn) == KERNFS_DIR)
		cgrp = kn->priv;
	else
		cgrp = kn->parent->priv;

	mutex_unlock(&cgroup_mutex);

	kernfs_unbreak_active_protection(kn);
	cgroup_put(cgrp);
}