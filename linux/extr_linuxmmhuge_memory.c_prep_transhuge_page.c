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
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANSHUGE_PAGE_DTOR ; 
 int /*<<< orphan*/  page_deferred_list (struct page*) ; 
 int /*<<< orphan*/  set_compound_page_dtor (struct page*,int /*<<< orphan*/ ) ; 

void prep_transhuge_page(struct page *page)
{
	/*
	 * we use page->mapping and page->indexlru in second tail page
	 * as list_head: assuming THP order >= 2
	 */

	INIT_LIST_HEAD(page_deferred_list(page));
	set_compound_page_dtor(page, TRANSHUGE_PAGE_DTOR);
}