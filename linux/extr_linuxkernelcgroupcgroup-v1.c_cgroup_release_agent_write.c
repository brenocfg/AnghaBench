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
struct kernfs_open_file {int /*<<< orphan*/  kn; } ;
struct cgroup {TYPE_1__* root; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  release_agent_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 size_t ENODEV ; 
 int PATH_MAX ; 
 struct cgroup* cgroup_kn_lock_live (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cgroup_kn_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_agent_path_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strstrip (char*) ; 

__attribute__((used)) static ssize_t cgroup_release_agent_write(struct kernfs_open_file *of,
					  char *buf, size_t nbytes, loff_t off)
{
	struct cgroup *cgrp;

	BUILD_BUG_ON(sizeof(cgrp->root->release_agent_path) < PATH_MAX);

	cgrp = cgroup_kn_lock_live(of->kn, false);
	if (!cgrp)
		return -ENODEV;
	spin_lock(&release_agent_path_lock);
	strlcpy(cgrp->root->release_agent_path, strstrip(buf),
		sizeof(cgrp->root->release_agent_path));
	spin_unlock(&release_agent_path_lock);
	cgroup_kn_unlock(of->kn);
	return nbytes;
}