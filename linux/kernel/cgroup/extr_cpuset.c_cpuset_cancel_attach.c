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
struct cgroup_taskset {int dummy; } ;
struct cgroup_subsys_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  attach_in_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_taskset_first (struct cgroup_taskset*,struct cgroup_subsys_state**) ; 
 int /*<<< orphan*/  cpuset_rwsem ; 
 TYPE_1__* css_cs (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  percpu_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpuset_cancel_attach(struct cgroup_taskset *tset)
{
	struct cgroup_subsys_state *css;

	cgroup_taskset_first(tset, &css);

	percpu_down_write(&cpuset_rwsem);
	css_cs(css)->attach_in_progress--;
	percpu_up_write(&cpuset_rwsem);
}