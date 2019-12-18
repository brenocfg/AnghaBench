#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ alloc; scalar_t__ pool_data; } ;
typedef  TYPE_1__ mempool_t ;

/* Variables and functions */
 int /*<<< orphan*/  kasan_alloc_pages (void*,unsigned long) ; 
 int /*<<< orphan*/  kasan_unpoison_slab (void*) ; 
 scalar_t__ mempool_alloc_pages ; 
 scalar_t__ mempool_alloc_slab ; 
 scalar_t__ mempool_kmalloc ; 

__attribute__((used)) static void kasan_unpoison_element(mempool_t *pool, void *element)
{
	if (pool->alloc == mempool_alloc_slab || pool->alloc == mempool_kmalloc)
		kasan_unpoison_slab(element);
	if (pool->alloc == mempool_alloc_pages)
		kasan_alloc_pages(element, (unsigned long)pool->pool_data);
}