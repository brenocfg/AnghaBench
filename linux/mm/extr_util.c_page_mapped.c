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
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 scalar_t__ PageHuge (struct page*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct page* compound_head (struct page*) ; 
 int /*<<< orphan*/ * compound_mapcount_ptr (struct page*) ; 
 int compound_nr (struct page*) ; 
 scalar_t__ likely (int) ; 

bool page_mapped(struct page *page)
{
	int i;

	if (likely(!PageCompound(page)))
		return atomic_read(&page->_mapcount) >= 0;
	page = compound_head(page);
	if (atomic_read(compound_mapcount_ptr(page)) >= 0)
		return true;
	if (PageHuge(page))
		return false;
	for (i = 0; i < compound_nr(page); i++) {
		if (atomic_read(&page[i]._mapcount) >= 0)
			return true;
	}
	return false;
}