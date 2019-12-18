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
struct cgroup_subsys {int dummy; } ;
struct cftype {char* name; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  __CFTYPE_ONLY_ON_DFL ; 
 int cgroup_add_cftypes (struct cgroup_subsys*,struct cftype*) ; 

int cgroup_add_dfl_cftypes(struct cgroup_subsys *ss, struct cftype *cfts)
{
	struct cftype *cft;

	for (cft = cfts; cft && cft->name[0] != '\0'; cft++)
		cft->flags |= __CFTYPE_ONLY_ON_DFL;
	return cgroup_add_cftypes(ss, cfts);
}