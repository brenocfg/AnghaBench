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
struct kmem_cache {int /*<<< orphan*/  flags; int /*<<< orphan*/  object_size; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  gfp_allowed_mask ; 
 void* kasan_slab_alloc (struct kmem_cache*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmemleak_alloc_recursive (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcg_kmem_enabled () ; 
 int /*<<< orphan*/  memcg_kmem_put_cache (struct kmem_cache*) ; 

__attribute__((used)) static inline void slab_post_alloc_hook(struct kmem_cache *s, gfp_t flags,
					size_t size, void **p)
{
	size_t i;

	flags &= gfp_allowed_mask;
	for (i = 0; i < size; i++) {
		p[i] = kasan_slab_alloc(s, p[i], flags);
		/* As p[i] might get tagged, call kmemleak hook after KASAN. */
		kmemleak_alloc_recursive(p[i], s->object_size, 1,
					 s->flags, flags);
	}

	if (memcg_kmem_enabled())
		memcg_kmem_put_cache(s);
}