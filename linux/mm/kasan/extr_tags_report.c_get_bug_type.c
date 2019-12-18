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
struct page {struct kmem_cache* slab_cache; } ;
struct kmem_cache {int dummy; } ;
struct kasan_alloc_meta {scalar_t__* free_pointer_tag; } ;
struct kasan_access_info {int /*<<< orphan*/  access_addr; } ;

/* Variables and functions */
 int KASAN_NR_FREE_STACKS ; 
 scalar_t__ PageSlab (struct page*) ; 
 struct kasan_alloc_meta* get_alloc_info (struct kmem_cache*,void*) ; 
 scalar_t__ get_tag (int /*<<< orphan*/ ) ; 
 struct page* kasan_addr_to_page (void const*) ; 
 void* nearest_obj (struct kmem_cache*,struct page*,void*) ; 
 void* reset_tag (int /*<<< orphan*/ ) ; 

const char *get_bug_type(struct kasan_access_info *info)
{
#ifdef CONFIG_KASAN_SW_TAGS_IDENTIFY
	struct kasan_alloc_meta *alloc_meta;
	struct kmem_cache *cache;
	struct page *page;
	const void *addr;
	void *object;
	u8 tag;
	int i;

	tag = get_tag(info->access_addr);
	addr = reset_tag(info->access_addr);
	page = kasan_addr_to_page(addr);
	if (page && PageSlab(page)) {
		cache = page->slab_cache;
		object = nearest_obj(cache, page, (void *)addr);
		alloc_meta = get_alloc_info(cache, object);

		for (i = 0; i < KASAN_NR_FREE_STACKS; i++)
			if (alloc_meta->free_pointer_tag[i] == tag)
				return "use-after-free";
		return "out-of-bounds";
	}

#endif
	return "invalid-access";
}