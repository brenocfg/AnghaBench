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
struct kmem_cache {int /*<<< orphan*/  cpu_slab; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_random_seq_destroy (struct kmem_cache*) ; 
 int /*<<< orphan*/  free_kmem_cache_nodes (struct kmem_cache*) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 

void __kmem_cache_release(struct kmem_cache *s)
{
	cache_random_seq_destroy(s);
	free_percpu(s->cpu_slab);
	free_kmem_cache_nodes(s);
}