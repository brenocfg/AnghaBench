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
struct mem_cgroup {int /*<<< orphan*/  memsw; int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCG_CACHE ; 
 int /*<<< orphan*/  MEMCG_RSS ; 
 int /*<<< orphan*/  MEMCG_SWAP ; 
 scalar_t__ mem_cgroup_is_root (struct mem_cgroup*) ; 
 unsigned long memcg_page_state (struct mem_cgroup*,int /*<<< orphan*/ ) ; 
 unsigned long page_counter_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long mem_cgroup_usage(struct mem_cgroup *memcg, bool swap)
{
	unsigned long val;

	if (mem_cgroup_is_root(memcg)) {
		val = memcg_page_state(memcg, MEMCG_CACHE) +
			memcg_page_state(memcg, MEMCG_RSS);
		if (swap)
			val += memcg_page_state(memcg, MEMCG_SWAP);
	} else {
		if (!swap)
			val = page_counter_read(&memcg->memory);
		else
			val = page_counter_read(&memcg->memsw);
	}
	return val;
}