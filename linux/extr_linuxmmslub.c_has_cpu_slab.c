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
struct kmem_cache_cpu {scalar_t__ page; } ;
struct kmem_cache {int /*<<< orphan*/  cpu_slab; } ;

/* Variables and functions */
 struct kmem_cache_cpu* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 scalar_t__ slub_percpu_partial (struct kmem_cache_cpu*) ; 

__attribute__((used)) static bool has_cpu_slab(int cpu, void *info)
{
	struct kmem_cache *s = info;
	struct kmem_cache_cpu *c = per_cpu_ptr(s->cpu_slab, cpu);

	return c->page || slub_percpu_partial(c);
}