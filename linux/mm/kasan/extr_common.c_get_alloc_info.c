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
struct TYPE_2__ {int alloc_meta_offset; } ;
struct kmem_cache {TYPE_1__ kasan_info; } ;
typedef  void kasan_alloc_meta ;

/* Variables and functions */

struct kasan_alloc_meta *get_alloc_info(struct kmem_cache *cache,
					const void *object)
{
	return (void *)object + cache->kasan_info.alloc_meta_offset;
}