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
typedef  size_t u8 ;
struct kmem_cache {int dummy; } ;
struct kasan_alloc_meta {size_t free_track_idx; size_t* free_pointer_tag; int /*<<< orphan*/ * free_track; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 size_t KASAN_NR_FREE_STACKS ; 
 struct kasan_alloc_meta* get_alloc_info (struct kmem_cache*,void*) ; 
 int /*<<< orphan*/  set_track (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kasan_set_free_info(struct kmem_cache *cache,
		void *object, u8 tag)
{
	struct kasan_alloc_meta *alloc_meta;
	u8 idx = 0;

	alloc_meta = get_alloc_info(cache, object);

#ifdef CONFIG_KASAN_SW_TAGS_IDENTIFY
	idx = alloc_meta->free_track_idx;
	alloc_meta->free_pointer_tag[idx] = tag;
	alloc_meta->free_track_idx = (idx + 1) % KASAN_NR_FREE_STACKS;
#endif

	set_track(&alloc_meta->free_track[idx], GFP_NOWAIT);
}