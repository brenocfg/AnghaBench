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
struct page {int dummy; } ;
struct kmem_cache {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void list_slab_objects(struct kmem_cache *s, struct page *page,
							const char *text)
{
#ifdef CONFIG_SLUB_DEBUG
	void *addr = page_address(page);
	void *p;
	unsigned long *map = kcalloc(BITS_TO_LONGS(page->objects),
				     sizeof(long),
				     GFP_ATOMIC);
	if (!map)
		return;
	slab_err(s, page, text, s->name);
	slab_lock(page);

	get_map(s, page, map);
	for_each_object(p, s, addr, page->objects) {

		if (!test_bit(slab_index(p, s, addr), map)) {
			pr_err("INFO: Object 0x%p @offset=%tu\n", p, p - addr);
			print_tracking(s, p);
		}
	}
	slab_unlock(page);
	kfree(map);
#endif
}