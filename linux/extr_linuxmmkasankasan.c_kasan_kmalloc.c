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
struct kmem_cache {unsigned long object_size; int flags; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  alloc_track; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASAN_KMALLOC_REDZONE ; 
 int /*<<< orphan*/  KASAN_SHADOW_SCALE_SIZE ; 
 int SLAB_KASAN ; 
 TYPE_1__* get_alloc_info (struct kmem_cache*,void const*) ; 
 scalar_t__ gfpflags_allow_blocking (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_poison_shadow (void*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_unpoison_shadow (void const*,size_t) ; 
 int /*<<< orphan*/  quarantine_reduce () ; 
 unsigned long round_up (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_track (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void kasan_kmalloc(struct kmem_cache *cache, const void *object, size_t size,
		   gfp_t flags)
{
	unsigned long redzone_start;
	unsigned long redzone_end;

	if (gfpflags_allow_blocking(flags))
		quarantine_reduce();

	if (unlikely(object == NULL))
		return;

	redzone_start = round_up((unsigned long)(object + size),
				KASAN_SHADOW_SCALE_SIZE);
	redzone_end = round_up((unsigned long)object + cache->object_size,
				KASAN_SHADOW_SCALE_SIZE);

	kasan_unpoison_shadow(object, size);
	kasan_poison_shadow((void *)redzone_start, redzone_end - redzone_start,
		KASAN_KMALLOC_REDZONE);

	if (cache->flags & SLAB_KASAN)
		set_track(&get_alloc_info(cache, object)->alloc_track, flags);
}