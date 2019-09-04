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
struct TYPE_2__ {scalar_t__ free_meta_offset; scalar_t__ alloc_meta_offset; } ;
struct kmem_cache {TYPE_1__ kasan_info; } ;
struct kasan_free_meta {int dummy; } ;
struct kasan_alloc_meta {int dummy; } ;

/* Variables and functions */

size_t kasan_metadata_size(struct kmem_cache *cache)
{
	return (cache->kasan_info.alloc_meta_offset ?
		sizeof(struct kasan_alloc_meta) : 0) +
		(cache->kasan_info.free_meta_offset ?
		sizeof(struct kasan_free_meta) : 0);
}