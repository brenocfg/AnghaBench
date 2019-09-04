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
struct kasan_alloc_meta {int /*<<< orphan*/  free_track; int /*<<< orphan*/  alloc_track; } ;

/* Variables and functions */
 int SLAB_KASAN ; 
 int /*<<< orphan*/  describe_object_addr (struct kmem_cache*,void*,void const*) ; 
 struct kasan_alloc_meta* get_alloc_info (struct kmem_cache*,void*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  print_track (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void describe_object(struct kmem_cache *cache, void *object,
				const void *addr)
{
	struct kasan_alloc_meta *alloc_info = get_alloc_info(cache, object);

	if (cache->flags & SLAB_KASAN) {
		print_track(&alloc_info->alloc_track, "Allocated");
		pr_err("\n");
		print_track(&alloc_info->free_track, "Freed");
		pr_err("\n");
	}

	describe_object_addr(cache, object, addr);
}