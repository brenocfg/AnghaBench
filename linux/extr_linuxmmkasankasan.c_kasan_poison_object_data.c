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
struct kmem_cache {int /*<<< orphan*/  object_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASAN_KMALLOC_REDZONE ; 
 int /*<<< orphan*/  KASAN_SHADOW_SCALE_SIZE ; 
 int /*<<< orphan*/  kasan_poison_shadow (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kasan_poison_object_data(struct kmem_cache *cache, void *object)
{
	kasan_poison_shadow(object,
			round_up(cache->object_size, KASAN_SHADOW_SCALE_SIZE),
			KASAN_KMALLOC_REDZONE);
}