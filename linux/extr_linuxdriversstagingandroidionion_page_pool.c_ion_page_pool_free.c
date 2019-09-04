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
struct ion_page_pool {scalar_t__ order; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ compound_order (struct page*) ; 
 int /*<<< orphan*/  ion_page_pool_add (struct ion_page_pool*,struct page*) ; 

void ion_page_pool_free(struct ion_page_pool *pool, struct page *page)
{
	BUG_ON(pool->order != compound_order(page));

	ion_page_pool_add(pool, page);
}