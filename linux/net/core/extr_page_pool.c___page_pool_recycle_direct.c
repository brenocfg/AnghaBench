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
struct TYPE_2__ {scalar_t__ count; struct page** cache; } ;
struct page_pool {TYPE_1__ alloc; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ PP_ALLOC_CACHE_SIZE ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool __page_pool_recycle_direct(struct page *page,
				       struct page_pool *pool)
{
	if (unlikely(pool->alloc.count == PP_ALLOC_CACHE_SIZE))
		return false;

	/* Caller MUST have verified/know (page_ref_count(page) == 1) */
	pool->alloc.cache[pool->alloc.count++] = page;
	return true;
}