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
struct kmem_cache {int flags; } ;
struct kasan_alloc_meta {int dummy; } ;

/* Variables and functions */
 int SLAB_KASAN ; 
 int /*<<< orphan*/  __memset (struct kasan_alloc_meta*,int /*<<< orphan*/ ,int) ; 
 struct kasan_alloc_meta* get_alloc_info (struct kmem_cache*,void const*) ; 

void kasan_init_slab_obj(struct kmem_cache *cache, const void *object)
{
	struct kasan_alloc_meta *alloc_info;

	if (!(cache->flags & SLAB_KASAN))
		return;

	alloc_info = get_alloc_info(cache, object);
	__memset(alloc_info, 0, sizeof(*alloc_info));
}