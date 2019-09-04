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
struct page {int /*<<< orphan*/  slab_cache; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  PageSlab (struct page*) ; 
 void const* ZERO_SIZE_PTR ; 
 int /*<<< orphan*/  kasan_kmalloc (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_kmalloc_large (void const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_head_page (void const*) ; 

void kasan_krealloc(const void *object, size_t size, gfp_t flags)
{
	struct page *page;

	if (unlikely(object == ZERO_SIZE_PTR))
		return;

	page = virt_to_head_page(object);

	if (unlikely(!PageSlab(page)))
		kasan_kmalloc_large(object, size, flags);
	else
		kasan_kmalloc(page->slab_cache, object, size, flags);
}