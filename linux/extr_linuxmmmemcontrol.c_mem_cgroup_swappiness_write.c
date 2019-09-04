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
typedef  int u64 ;
struct mem_cgroup {int swappiness; } ;
struct cgroup_subsys_state {scalar_t__ parent; } ;
struct cftype {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mem_cgroup* mem_cgroup_from_css (struct cgroup_subsys_state*) ; 
 int vm_swappiness ; 

__attribute__((used)) static int mem_cgroup_swappiness_write(struct cgroup_subsys_state *css,
				       struct cftype *cft, u64 val)
{
	struct mem_cgroup *memcg = mem_cgroup_from_css(css);

	if (val > 100)
		return -EINVAL;

	if (css->parent)
		memcg->swappiness = val;
	else
		vm_swappiness = val;

	return 0;
}