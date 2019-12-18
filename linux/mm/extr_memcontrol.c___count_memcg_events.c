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
struct mem_cgroup {TYPE_2__* vmstats_percpu; int /*<<< orphan*/ * vmevents; TYPE_1__* vmstats_local; } ;
typedef  enum vm_event_item { ____Placeholder_vm_event_item } vm_event_item ;
struct TYPE_4__ {int /*<<< orphan*/ * events; } ;
struct TYPE_3__ {int /*<<< orphan*/ * events; } ;

/* Variables and functions */
 unsigned long MEMCG_CHARGE_BATCH ; 
 int /*<<< orphan*/  __this_cpu_add (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  atomic_long_add (unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ mem_cgroup_disabled () ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 
 scalar_t__ unlikely (int) ; 

void __count_memcg_events(struct mem_cgroup *memcg, enum vm_event_item idx,
			  unsigned long count)
{
	unsigned long x;

	if (mem_cgroup_disabled())
		return;

	x = count + __this_cpu_read(memcg->vmstats_percpu->events[idx]);
	if (unlikely(x > MEMCG_CHARGE_BATCH)) {
		struct mem_cgroup *mi;

		/*
		 * Batch local counters to keep them in sync with
		 * the hierarchical ones.
		 */
		__this_cpu_add(memcg->vmstats_local->events[idx], x);
		for (mi = memcg; mi; mi = parent_mem_cgroup(mi))
			atomic_long_add(x, &mi->vmevents[idx]);
		x = 0;
	}
	__this_cpu_write(memcg->vmstats_percpu->events[idx], x);
}