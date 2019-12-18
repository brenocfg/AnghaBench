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
 int /*<<< orphan*/  __invalidate_reclaim_iterators (struct mem_cgroup*,struct mem_cgroup*) ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 
 struct mem_cgroup* root_mem_cgroup ; 

__attribute__((used)) static void invalidate_reclaim_iterators(struct mem_cgroup *dead_memcg)
{
	struct mem_cgroup *memcg = dead_memcg;
	struct mem_cgroup *last;

	do {
		__invalidate_reclaim_iterators(memcg, dead_memcg);
		last = memcg;
	} while ((memcg = parent_mem_cgroup(memcg)));

	/*
	 * When cgruop1 non-hierarchy mode is used,
	 * parent_mem_cgroup() does not walk all the way up to the
	 * cgroup root (root_mem_cgroup). So we have to handle
	 * dead_memcg from cgroup root separately.
	 */
	if (last != root_mem_cgroup)
		__invalidate_reclaim_iterators(root_mem_cgroup,
						dead_memcg);
}