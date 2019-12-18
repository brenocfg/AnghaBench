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
typedef  scalar_t__ u8 ;
struct kmem_cache {int dummy; } ;
struct kasan_track {int dummy; } ;
struct kasan_alloc_meta {scalar_t__* free_pointer_tag; int free_track_idx; struct kasan_track* free_track; } ;

/* Variables and functions */
 int KASAN_NR_FREE_STACKS ; 
 struct kasan_alloc_meta* get_alloc_info (struct kmem_cache*,void*) ; 

__attribute__((used)) static struct kasan_track *kasan_get_free_track(struct kmem_cache *cache,
		void *object, u8 tag)
{
	struct kasan_alloc_meta *alloc_meta;
	int i = 0;

	alloc_meta = get_alloc_info(cache, object);

#ifdef CONFIG_KASAN_SW_TAGS_IDENTIFY
	for (i = 0; i < KASAN_NR_FREE_STACKS; i++) {
		if (alloc_meta->free_pointer_tag[i] == tag)
			break;
	}
	if (i == KASAN_NR_FREE_STACKS)
		i = alloc_meta->free_track_idx;
#endif

	return &alloc_meta->free_track[i];
}