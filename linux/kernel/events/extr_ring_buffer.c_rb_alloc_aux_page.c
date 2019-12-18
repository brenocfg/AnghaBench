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

/* Variables and functions */
 int MAX_ORDER ; 
 int /*<<< orphan*/  PERF_AUX_GFP ; 
 int /*<<< orphan*/  SetPagePrivate (struct page*) ; 
 struct page* alloc_pages_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int) ; 
 int /*<<< orphan*/  split_page (struct page*,int) ; 

__attribute__((used)) static struct page *rb_alloc_aux_page(int node, int order)
{
	struct page *page;

	if (order > MAX_ORDER)
		order = MAX_ORDER;

	do {
		page = alloc_pages_node(node, PERF_AUX_GFP, order);
	} while (!page && order--);

	if (page && order) {
		/*
		 * Communicate the allocation size to the driver:
		 * if we managed to secure a high-order allocation,
		 * set its first page's private to this order;
		 * !PagePrivate(page) means it's just a normal page.
		 */
		split_page(page, order);
		SetPagePrivate(page);
		set_page_private(page, order);
	}

	return page;
}