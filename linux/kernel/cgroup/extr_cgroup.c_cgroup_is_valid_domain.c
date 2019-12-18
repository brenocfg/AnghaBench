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
struct cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_is_mixable (struct cgroup*) ; 
 scalar_t__ cgroup_is_thread_root (struct cgroup*) ; 
 scalar_t__ cgroup_is_threaded (struct cgroup*) ; 
 struct cgroup* cgroup_parent (struct cgroup*) ; 

__attribute__((used)) static bool cgroup_is_valid_domain(struct cgroup *cgrp)
{
	/* the cgroup itself can be a thread root */
	if (cgroup_is_threaded(cgrp))
		return false;

	/* but the ancestors can't be unless mixable */
	while ((cgrp = cgroup_parent(cgrp))) {
		if (!cgroup_is_mixable(cgrp) && cgroup_is_thread_root(cgrp))
			return false;
		if (cgroup_is_threaded(cgrp))
			return false;
	}

	return true;
}