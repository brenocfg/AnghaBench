#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mem_cgroup {TYPE_2__* vmstats_percpu; int /*<<< orphan*/ * vmstats; TYPE_1__* vmstats_local; } ;
struct TYPE_4__ {int /*<<< orphan*/ * stat; } ;
struct TYPE_3__ {int /*<<< orphan*/ * stat; } ;

/* Variables and functions */
 scalar_t__ MEMCG_CHARGE_BATCH ; 
 int /*<<< orphan*/  __this_cpu_add (int /*<<< orphan*/ ,long) ; 
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,long) ; 
 scalar_t__ abs (long) ; 
 int /*<<< orphan*/  atomic_long_add (long,int /*<<< orphan*/ *) ; 
 scalar_t__ mem_cgroup_disabled () ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 
 scalar_t__ unlikely (int) ; 

void __mod_memcg_state(struct mem_cgroup *memcg, int idx, int val)
{
	long x;

	if (mem_cgroup_disabled())
		return;

	x = val + __this_cpu_read(memcg->vmstats_percpu->stat[idx]);
	if (unlikely(abs(x) > MEMCG_CHARGE_BATCH)) {
		struct mem_cgroup *mi;

		/*
		 * Batch local counters to keep them in sync with
		 * the hierarchical ones.
		 */
		__this_cpu_add(memcg->vmstats_local->stat[idx], x);
		for (mi = memcg; mi; mi = parent_mem_cgroup(mi))
			atomic_long_add(x, &mi->vmstats[idx]);
		x = 0;
	}
	__this_cpu_write(memcg->vmstats_percpu->stat[idx], x);
}