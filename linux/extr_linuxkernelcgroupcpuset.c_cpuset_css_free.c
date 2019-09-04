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
struct cpuset {int /*<<< orphan*/  cpus_allowed; int /*<<< orphan*/  effective_cpus; } ;
struct cgroup_subsys_state {int dummy; } ;

/* Variables and functions */
 struct cpuset* css_cs (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cpuset*) ; 

__attribute__((used)) static void cpuset_css_free(struct cgroup_subsys_state *css)
{
	struct cpuset *cs = css_cs(css);

	free_cpumask_var(cs->effective_cpus);
	free_cpumask_var(cs->cpus_allowed);
	kfree(cs);
}