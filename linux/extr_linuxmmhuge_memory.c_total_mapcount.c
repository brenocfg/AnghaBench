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
 int HPAGE_PMD_NR ; 
 int /*<<< orphan*/  PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageCompound (struct page*) ; 
 scalar_t__ PageDoubleMap (struct page*) ; 
 scalar_t__ PageHuge (struct page*) ; 
 int /*<<< orphan*/  PageTail (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int /*<<< orphan*/ ,struct page*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int compound_mapcount (struct page*) ; 
 scalar_t__ likely (int) ; 

int total_mapcount(struct page *page)
{
	int i, compound, ret;

	VM_BUG_ON_PAGE(PageTail(page), page);

	if (likely(!PageCompound(page)))
		return atomic_read(&page->_mapcount) + 1;

	compound = compound_mapcount(page);
	if (PageHuge(page))
		return compound;
	ret = compound;
	for (i = 0; i < HPAGE_PMD_NR; i++)
		ret += atomic_read(&page[i]._mapcount) + 1;
	/* File pages has compound_mapcount included in _mapcount */
	if (!PageAnon(page))
		return ret - compound * HPAGE_PMD_NR;
	if (PageDoubleMap(page))
		ret -= HPAGE_PMD_NR;
	return ret;
}