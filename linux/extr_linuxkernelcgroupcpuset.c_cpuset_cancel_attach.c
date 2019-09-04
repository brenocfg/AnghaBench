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
struct cpuset {int /*<<< orphan*/  attach_in_progress; } ;
struct cgroup_taskset {int dummy; } ;
struct cgroup_subsys_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_taskset_first (struct cgroup_taskset*,struct cgroup_subsys_state**) ; 
 int /*<<< orphan*/  cpuset_mutex ; 
 struct cpuset* css_cs (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpuset_cancel_attach(struct cgroup_taskset *tset)
{
	struct cgroup_subsys_state *css;
	struct cpuset *cs;

	cgroup_taskset_first(tset, &css);
	cs = css_cs(css);

	mutex_lock(&cpuset_mutex);
	css_cs(css)->attach_in_progress--;
	mutex_unlock(&cpuset_mutex);
}