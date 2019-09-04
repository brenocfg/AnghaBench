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
struct page_counter {int dummy; } ;
struct mem_cgroup {int tcpmem_pressure; int /*<<< orphan*/  tcpmem; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int GFP_NOWAIT ; 
 int /*<<< orphan*/  MEMCG_SOCK ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  cgroup_subsys_on_dfl (int /*<<< orphan*/ ) ; 
 scalar_t__ in_softirq () ; 
 int /*<<< orphan*/  memory_cgrp_subsys ; 
 int /*<<< orphan*/  mod_memcg_state (struct mem_cgroup*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  page_counter_charge (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ page_counter_try_charge (int /*<<< orphan*/ *,unsigned int,struct page_counter**) ; 
 scalar_t__ try_charge (struct mem_cgroup*,int,unsigned int) ; 

bool mem_cgroup_charge_skmem(struct mem_cgroup *memcg, unsigned int nr_pages)
{
	gfp_t gfp_mask = GFP_KERNEL;

	if (!cgroup_subsys_on_dfl(memory_cgrp_subsys)) {
		struct page_counter *fail;

		if (page_counter_try_charge(&memcg->tcpmem, nr_pages, &fail)) {
			memcg->tcpmem_pressure = 0;
			return true;
		}
		page_counter_charge(&memcg->tcpmem, nr_pages);
		memcg->tcpmem_pressure = 1;
		return false;
	}

	/* Don't block in the packet receive path */
	if (in_softirq())
		gfp_mask = GFP_NOWAIT;

	mod_memcg_state(memcg, MEMCG_SOCK, nr_pages);

	if (try_charge(memcg, gfp_mask, nr_pages) == 0)
		return true;

	try_charge(memcg, gfp_mask|__GFP_NOFAIL, nr_pages);
	return false;
}