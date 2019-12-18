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
 int /*<<< orphan*/  flush_slab (struct kmem_cache*,struct kmem_cache_cpu*) ; 
 struct kmem_cache_cpu* per_cpu_ptr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unfreeze_partials (struct kmem_cache*,struct kmem_cache_cpu*) ; 

__attribute__((used)) static inline void __flush_cpu_slab(struct kmem_cache *s, int cpu)
{
	struct kmem_cache_cpu *c = per_cpu_ptr(s->cpu_slab, cpu);

	if (c->page)
		flush_slab(s, c);

	unfreeze_partials(s, c);
}