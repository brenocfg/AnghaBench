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
struct cgroup_namespace {int /*<<< orphan*/  root_cset; } ;
struct cgroup {int /*<<< orphan*/  kn; int /*<<< orphan*/  root; } ;

/* Variables and functions */
 struct cgroup* cset_cgroup_from_root (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kernfs_path_from_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 

int cgroup_path_ns_locked(struct cgroup *cgrp, char *buf, size_t buflen,
			  struct cgroup_namespace *ns)
{
	struct cgroup *root = cset_cgroup_from_root(ns->root_cset, cgrp->root);

	return kernfs_path_from_node(cgrp->kn, root->kn, buf, buflen);
}