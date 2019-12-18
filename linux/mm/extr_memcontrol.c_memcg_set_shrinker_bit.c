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
struct memcg_shrinker_map {int /*<<< orphan*/  map; } ;
struct mem_cgroup {TYPE_1__** nodeinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  shrinker_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  mem_cgroup_is_root (struct mem_cgroup*) ; 
 struct memcg_shrinker_map* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

void memcg_set_shrinker_bit(struct mem_cgroup *memcg, int nid, int shrinker_id)
{
	if (shrinker_id >= 0 && memcg && !mem_cgroup_is_root(memcg)) {
		struct memcg_shrinker_map *map;

		rcu_read_lock();
		map = rcu_dereference(memcg->nodeinfo[nid]->shrinker_map);
		/* Pairs with smp mb in shrink_slab() */
		smp_mb__before_atomic();
		set_bit(shrinker_id, map->map);
		rcu_read_unlock();
	}
}