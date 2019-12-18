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
struct mem_cgroup {scalar_t__ high; int /*<<< orphan*/  memory; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  MEMCG_HIGH ; 
 int /*<<< orphan*/  memcg_memory_event (struct mem_cgroup*,int /*<<< orphan*/ ) ; 
 scalar_t__ page_counter_read (int /*<<< orphan*/ *) ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 
 int /*<<< orphan*/  try_to_free_mem_cgroup_pages (struct mem_cgroup*,unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reclaim_high(struct mem_cgroup *memcg,
			 unsigned int nr_pages,
			 gfp_t gfp_mask)
{
	do {
		if (page_counter_read(&memcg->memory) <= memcg->high)
			continue;
		memcg_memory_event(memcg, MEMCG_HIGH);
		try_to_free_mem_cgroup_pages(memcg, nr_pages, gfp_mask, true);
	} while ((memcg = parent_mem_cgroup(memcg)));
}