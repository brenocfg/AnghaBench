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
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mem_cgroup* mem_cgroup_iter (int /*<<< orphan*/ *,struct mem_cgroup*,int /*<<< orphan*/ *) ; 
 scalar_t__ shrink_slab (int /*<<< orphan*/ ,int,struct mem_cgroup*,int /*<<< orphan*/ ) ; 

void drop_slab_node(int nid)
{
	unsigned long freed;

	do {
		struct mem_cgroup *memcg = NULL;

		freed = 0;
		memcg = mem_cgroup_iter(NULL, NULL, NULL);
		do {
			freed += shrink_slab(GFP_KERNEL, nid, memcg, 0);
		} while ((memcg = mem_cgroup_iter(NULL, memcg, NULL)) != NULL);
	} while (freed > 10);
}