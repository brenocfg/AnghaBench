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
typedef  unsigned long pgoff_t ;

/* Variables and functions */
 unsigned long MAX_ORDER ; 
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 struct page* compound_head (struct page*) ; 
 unsigned long compound_order (struct page*) ; 
 unsigned long page_index (struct page*) ; 
 unsigned long page_to_pfn (struct page*) ; 

pgoff_t __basepage_index(struct page *page)
{
	struct page *page_head = compound_head(page);
	pgoff_t index = page_index(page_head);
	unsigned long compound_idx;

	if (!PageHuge(page_head))
		return page_index(page);

	if (compound_order(page_head) >= MAX_ORDER)
		compound_idx = page_to_pfn(page) - page_to_pfn(page_head);
	else
		compound_idx = page - page_head;

	return (index << compound_order(page_head)) + compound_idx;
}