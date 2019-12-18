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
struct oom_control {int /*<<< orphan*/  order; int /*<<< orphan*/  gfp_mask; int /*<<< orphan*/ * memcg; int /*<<< orphan*/ * nodemask; int /*<<< orphan*/ * zonelist; } ;

/* Variables and functions */
 scalar_t__ mem_cgroup_oom_synchronize (int) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oom_lock ; 
 int /*<<< orphan*/  out_of_memory (struct oom_control*) ; 

void pagefault_out_of_memory(void)
{
	struct oom_control oc = {
		.zonelist = NULL,
		.nodemask = NULL,
		.memcg = NULL,
		.gfp_mask = 0,
		.order = 0,
	};

	if (mem_cgroup_oom_synchronize(true))
		return;

	if (!mutex_trylock(&oom_lock))
		return;
	out_of_memory(&oc);
	mutex_unlock(&oom_lock);
}