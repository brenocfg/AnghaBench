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
struct cgroup_subsys_state {int dummy; } ;
struct cgroup_subsys {size_t id; } ;
struct cgroup {int dummy; } ;
struct TYPE_2__ {struct cgroup_subsys_state** subsys; } ;

/* Variables and functions */
 struct cgroup_subsys_state* cgroup_css (struct cgroup*,struct cgroup_subsys*) ; 
 struct cgroup* cgroup_parent (struct cgroup*) ; 
 TYPE_1__ init_css_set ; 

struct cgroup_subsys_state *cgroup_e_css(struct cgroup *cgrp,
					 struct cgroup_subsys *ss)
{
	struct cgroup_subsys_state *css;

	do {
		css = cgroup_css(cgrp, ss);

		if (css)
			return css;
		cgrp = cgroup_parent(cgrp);
	} while (cgrp);

	return init_css_set.subsys[ss->id];
}