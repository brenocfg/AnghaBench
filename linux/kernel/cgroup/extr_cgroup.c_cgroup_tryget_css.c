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
struct cgroup_subsys_state {int dummy; } ;
struct cgroup_subsys {int dummy; } ;
struct cgroup {int dummy; } ;

/* Variables and functions */
 struct cgroup_subsys_state* cgroup_css (struct cgroup*,struct cgroup_subsys*) ; 
 int /*<<< orphan*/  css_tryget_online (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct cgroup_subsys_state *cgroup_tryget_css(struct cgroup *cgrp,
						     struct cgroup_subsys *ss)
{
	struct cgroup_subsys_state *css;

	rcu_read_lock();
	css = cgroup_css(cgrp, ss);
	if (css && !css_tryget_online(css))
		css = NULL;
	rcu_read_unlock();

	return css;
}