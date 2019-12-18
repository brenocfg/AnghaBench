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
struct cgroup {int /*<<< orphan*/  release_agent_work; int /*<<< orphan*/  self; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_is_dead (struct cgroup*) ; 
 int /*<<< orphan*/  cgroup_is_populated (struct cgroup*) ; 
 int /*<<< orphan*/  css_has_online_children (int /*<<< orphan*/ *) ; 
 scalar_t__ notify_on_release (struct cgroup*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void cgroup1_check_for_release(struct cgroup *cgrp)
{
	if (notify_on_release(cgrp) && !cgroup_is_populated(cgrp) &&
	    !css_has_online_children(&cgrp->self) && !cgroup_is_dead(cgrp))
		schedule_work(&cgrp->release_agent_work);
}