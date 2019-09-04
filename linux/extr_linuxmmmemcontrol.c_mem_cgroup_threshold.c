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
struct mem_cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mem_cgroup_threshold (struct mem_cgroup*,int) ; 
 scalar_t__ do_memsw_account () ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 

__attribute__((used)) static void mem_cgroup_threshold(struct mem_cgroup *memcg)
{
	while (memcg) {
		__mem_cgroup_threshold(memcg, false);
		if (do_memsw_account())
			__mem_cgroup_threshold(memcg, true);

		memcg = parent_mem_cgroup(memcg);
	}
}