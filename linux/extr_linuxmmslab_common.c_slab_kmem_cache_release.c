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
struct kmem_cache {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kmem_cache_release (struct kmem_cache*) ; 
 int /*<<< orphan*/  destroy_memcg_params (struct kmem_cache*) ; 
 int /*<<< orphan*/  kfree_const (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kmem_cache*) ; 

void slab_kmem_cache_release(struct kmem_cache *s)
{
	__kmem_cache_release(s);
	destroy_memcg_params(s);
	kfree_const(s->name);
	kmem_cache_free(kmem_cache, s);
}