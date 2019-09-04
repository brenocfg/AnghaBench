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
struct page {int /*<<< orphan*/  _mapcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 scalar_t__ PageDoubleMap (struct page*) ; 
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/ * compound_mapcount_ptr (struct page*) ; 

int __page_mapcount(struct page *page)
{
	int ret;

	ret = atomic_read(&page->_mapcount) + 1;
	/*
	 * For file THP page->_mapcount contains total number of mapping
	 * of the page: no need to look into compound_mapcount.
	 */
	if (!PageAnon(page) && !PageHuge(page))
		return ret;
	page = compound_head(page);
	ret += atomic_read(compound_mapcount_ptr(page)) + 1;
	if (PageDoubleMap(page))
		ret--;
	return ret;
}