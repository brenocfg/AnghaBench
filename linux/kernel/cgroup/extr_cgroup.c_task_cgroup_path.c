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
struct task_struct {int dummy; } ;
struct cgroup_root {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_hierarchy_idr ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int cgroup_path_ns_locked (struct cgroup*,char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  css_set_lock ; 
 struct cgroup_root* idr_get_next (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  init_cgroup_ns ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int strlcpy (char*,char*,size_t) ; 
 struct cgroup* task_cgroup_from_root (struct task_struct*,struct cgroup_root*) ; 

int task_cgroup_path(struct task_struct *task, char *buf, size_t buflen)
{
	struct cgroup_root *root;
	struct cgroup *cgrp;
	int hierarchy_id = 1;
	int ret;

	mutex_lock(&cgroup_mutex);
	spin_lock_irq(&css_set_lock);

	root = idr_get_next(&cgroup_hierarchy_idr, &hierarchy_id);

	if (root) {
		cgrp = task_cgroup_from_root(task, root);
		ret = cgroup_path_ns_locked(cgrp, buf, buflen, &init_cgroup_ns);
	} else {
		/* if no hierarchy exists, everyone is in "/" */
		ret = strlcpy(buf, "/", buflen);
	}

	spin_unlock_irq(&css_set_lock);
	mutex_unlock(&cgroup_mutex);
	return ret;
}