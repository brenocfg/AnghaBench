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
struct kmem_cache {TYPE_1__* cpu_slab; } ;
typedef  enum stat_item { ____Placeholder_stat_item } stat_item ;
struct TYPE_2__ {int /*<<< orphan*/ * stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw_cpu_inc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void stat(const struct kmem_cache *s, enum stat_item si)
{
#ifdef CONFIG_SLUB_STATS
	/*
	 * The rmw is racy on a preemptible kernel but this is acceptable, so
	 * avoid this_cpu_add()'s irq-disable overhead.
	 */
	raw_cpu_inc(s->cpu_slab->stat[si]);
#endif
}