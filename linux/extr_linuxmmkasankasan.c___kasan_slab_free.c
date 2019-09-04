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
struct kmem_cache {int flags; int /*<<< orphan*/  object_size; } ;
typedef  scalar_t__ s8 ;
struct TYPE_2__ {int /*<<< orphan*/  free_track; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  KASAN_KMALLOC_FREE ; 
 scalar_t__ KASAN_SHADOW_SCALE_SIZE ; 
 scalar_t__ READ_ONCE (scalar_t__) ; 
 int SLAB_KASAN ; 
 int SLAB_TYPESAFE_BY_RCU ; 
 TYPE_1__* get_alloc_info (struct kmem_cache*,void*) ; 
 int /*<<< orphan*/  get_free_info (struct kmem_cache*,void*) ; 
 scalar_t__ kasan_mem_to_shadow (void*) ; 
 int /*<<< orphan*/  kasan_poison_shadow (void*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_report_invalid_free (void*,unsigned long) ; 
 void* nearest_obj (struct kmem_cache*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  quarantine_put (int /*<<< orphan*/ ,struct kmem_cache*) ; 
 unsigned long round_up (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_track (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virt_to_head_page (void*) ; 

__attribute__((used)) static bool __kasan_slab_free(struct kmem_cache *cache, void *object,
			      unsigned long ip, bool quarantine)
{
	s8 shadow_byte;
	unsigned long rounded_up_size;

	if (unlikely(nearest_obj(cache, virt_to_head_page(object), object) !=
	    object)) {
		kasan_report_invalid_free(object, ip);
		return true;
	}

	/* RCU slabs could be legally used after free within the RCU period */
	if (unlikely(cache->flags & SLAB_TYPESAFE_BY_RCU))
		return false;

	shadow_byte = READ_ONCE(*(s8 *)kasan_mem_to_shadow(object));
	if (shadow_byte < 0 || shadow_byte >= KASAN_SHADOW_SCALE_SIZE) {
		kasan_report_invalid_free(object, ip);
		return true;
	}

	rounded_up_size = round_up(cache->object_size, KASAN_SHADOW_SCALE_SIZE);
	kasan_poison_shadow(object, rounded_up_size, KASAN_KMALLOC_FREE);

	if (!quarantine || unlikely(!(cache->flags & SLAB_KASAN)))
		return false;

	set_track(&get_alloc_info(cache, object)->free_track, GFP_NOWAIT);
	quarantine_put(get_free_info(cache, object), cache);
	return true;
}