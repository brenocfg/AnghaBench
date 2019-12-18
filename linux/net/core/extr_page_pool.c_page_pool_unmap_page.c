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

/* Variables and functions */
 int /*<<< orphan*/  __page_pool_clean_page (struct page_pool*,struct page*) ; 

void page_pool_unmap_page(struct page_pool *pool, struct page *page)
{
	/* When page is unmapped, this implies page will not be
	 * returned to page_pool.
	 */
	__page_pool_clean_page(pool, page);
}