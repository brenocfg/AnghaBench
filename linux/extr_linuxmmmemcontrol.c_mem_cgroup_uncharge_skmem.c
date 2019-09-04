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
struct mem_cgroup {int /*<<< orphan*/  tcpmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCG_SOCK ; 
 int /*<<< orphan*/  cgroup_subsys_on_dfl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_cgrp_subsys ; 
 int /*<<< orphan*/  mod_memcg_state (struct mem_cgroup*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  page_counter_uncharge (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  refill_stock (struct mem_cgroup*,unsigned int) ; 

void mem_cgroup_uncharge_skmem(struct mem_cgroup *memcg, unsigned int nr_pages)
{
	if (!cgroup_subsys_on_dfl(memory_cgrp_subsys)) {
		page_counter_uncharge(&memcg->tcpmem, nr_pages);
		return;
	}

	mod_memcg_state(memcg, MEMCG_SOCK, -nr_pages);

	refill_stock(memcg, nr_pages);
}