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
struct cpuset {int /*<<< orphan*/  relax_domain_level; } ;
struct cgroup_subsys_state {int dummy; } ;
struct cftype {int private; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  int cpuset_filetype_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  FILE_SCHED_RELAX_DOMAIN_LEVEL 128 
 struct cpuset* css_cs (struct cgroup_subsys_state*) ; 

__attribute__((used)) static s64 cpuset_read_s64(struct cgroup_subsys_state *css, struct cftype *cft)
{
	struct cpuset *cs = css_cs(css);
	cpuset_filetype_t type = cft->private;
	switch (type) {
	case FILE_SCHED_RELAX_DOMAIN_LEVEL:
		return cs->relax_domain_level;
	default:
		BUG();
	}

	/* Unrechable but makes gcc happy */
	return 0;
}