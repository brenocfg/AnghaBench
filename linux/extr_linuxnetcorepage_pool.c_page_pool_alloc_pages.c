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
struct page_pool {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct page* __page_pool_alloc_pages_slow (struct page_pool*,int /*<<< orphan*/ ) ; 
 struct page* __page_pool_get_cached (struct page_pool*) ; 

struct page *page_pool_alloc_pages(struct page_pool *pool, gfp_t gfp)
{
	struct page *page;

	/* Fast-path: Get a page from cache */
	page = __page_pool_get_cached(pool);
	if (page)
		return page;

	/* Slow-path: cache empty, do real allocation */
	page = __page_pool_alloc_pages_slow(pool, gfp);
	return page;
}