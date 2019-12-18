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
struct page {scalar_t__ compound_dtor; } ;

/* Variables and functions */
 scalar_t__ HUGETLB_PAGE_DTOR ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 struct page* compound_head (struct page*) ; 

int PageHuge(struct page *page)
{
	if (!PageCompound(page))
		return 0;

	page = compound_head(page);
	return page[1].compound_dtor == HUGETLB_PAGE_DTOR;
}