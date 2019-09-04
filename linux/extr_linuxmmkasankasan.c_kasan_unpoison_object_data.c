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
 int /*<<< orphan*/  kasan_unpoison_shadow (void*,int /*<<< orphan*/ ) ; 

void kasan_unpoison_object_data(struct kmem_cache *cache, void *object)
{
	kasan_unpoison_shadow(object, cache->object_size);
}