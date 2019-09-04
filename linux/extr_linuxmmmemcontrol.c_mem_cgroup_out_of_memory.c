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
struct oom_control {int order; int /*<<< orphan*/  gfp_mask; struct mem_cgroup* memcg; int /*<<< orphan*/ * nodemask; int /*<<< orphan*/ * zonelist; } ;
struct mem_cgroup {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ mutex_lock_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oom_lock ; 
 scalar_t__ out_of_memory (struct oom_control*) ; 
 scalar_t__ should_force_charge () ; 

__attribute__((used)) static bool mem_cgroup_out_of_memory(struct mem_cgroup *memcg, gfp_t gfp_mask,
				     int order)
{
	struct oom_control oc = {
		.zonelist = NULL,
		.nodemask = NULL,
		.memcg = memcg,
		.gfp_mask = gfp_mask,
		.order = order,
	};
	bool ret;

	if (mutex_lock_killable(&oom_lock))
		return true;
	/*
	 * A few threads which were not waiting at mutex_lock_killable() can
	 * fail to bail out. Therefore, check again after holding oom_lock.
	 */
	ret = should_force_charge() || out_of_memory(&oc);
	mutex_unlock(&oom_lock);
	return ret;
}