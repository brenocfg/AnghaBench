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
struct page_pool {int /*<<< orphan*/  ring; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ in_serving_softirq () ; 
 int ptr_ring_produce (int /*<<< orphan*/ *,struct page*) ; 
 int ptr_ring_produce_bh (int /*<<< orphan*/ *,struct page*) ; 

__attribute__((used)) static bool __page_pool_recycle_into_ring(struct page_pool *pool,
				   struct page *page)
{
	int ret;
	/* BH protection not needed if current is serving softirq */
	if (in_serving_softirq())
		ret = ptr_ring_produce(&pool->ring, page);
	else
		ret = ptr_ring_produce_bh(&pool->ring, page);

	return (ret == 0) ? true : false;
}