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
struct cgroup_subsys {size_t id; } ;
struct cgroup {struct cgroup_subsys_state self; int /*<<< orphan*/ * subsys; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct cgroup_subsys_state* rcu_dereference_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cgroup_subsys_state *cgroup_css(struct cgroup *cgrp,
					      struct cgroup_subsys *ss)
{
	if (ss)
		return rcu_dereference_check(cgrp->subsys[ss->id],
					lockdep_is_held(&cgroup_mutex));
	else
		return &cgrp->self;
}