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
struct ion_system_heap {struct ion_page_pool** pools; } ;
struct ion_page_pool {int dummy; } ;
struct ion_buffer {int private_flags; } ;

/* Variables and functions */
 int ION_PRIV_FLAG_SHRINKER_FREE ; 
 int /*<<< orphan*/  __free_pages (struct page*,unsigned int) ; 
 unsigned int compound_order (struct page*) ; 
 int /*<<< orphan*/  ion_page_pool_free (struct ion_page_pool*,struct page*) ; 
 size_t order_to_index (unsigned int) ; 

__attribute__((used)) static void free_buffer_page(struct ion_system_heap *heap,
			     struct ion_buffer *buffer, struct page *page)
{
	struct ion_page_pool *pool;
	unsigned int order = compound_order(page);

	/* go to system */
	if (buffer->private_flags & ION_PRIV_FLAG_SHRINKER_FREE) {
		__free_pages(page, order);
		return;
	}

	pool = heap->pools[order_to_index(order)];

	ion_page_pool_free(pool, page);
}