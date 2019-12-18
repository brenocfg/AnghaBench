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
struct cgroup_namespace {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_mutex ; 
 int cgroup_path_ns_locked (struct cgroup*,char*,size_t,struct cgroup_namespace*) ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int cgroup_path_ns(struct cgroup *cgrp, char *buf, size_t buflen,
		   struct cgroup_namespace *ns)
{
	int ret;

	mutex_lock(&cgroup_mutex);
	spin_lock_irq(&css_set_lock);

	ret = cgroup_path_ns_locked(cgrp, buf, buflen, ns);

	spin_unlock_irq(&css_set_lock);
	mutex_unlock(&cgroup_mutex);

	return ret;
}