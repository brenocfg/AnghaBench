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
 int /*<<< orphan*/  PageHead (struct page*) ; 
 scalar_t__ free_huge_page ; 
 scalar_t__ get_compound_page_dtor (struct page*) ; 

int PageHeadHuge(struct page *page_head)
{
	if (!PageHead(page_head))
		return 0;

	return get_compound_page_dtor(page_head) == free_huge_page;
}