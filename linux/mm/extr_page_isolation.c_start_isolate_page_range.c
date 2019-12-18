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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,scalar_t__) ; 
 struct page* __first_valid_page (unsigned long,scalar_t__) ; 
 scalar_t__ pageblock_nr_pages ; 
 struct page* pfn_to_online_page (unsigned long) ; 
 scalar_t__ set_migratetype_isolate (struct page*,unsigned int,int) ; 
 int /*<<< orphan*/  unset_migratetype_isolate (struct page*,unsigned int) ; 

int start_isolate_page_range(unsigned long start_pfn, unsigned long end_pfn,
			     unsigned migratetype, int flags)
{
	unsigned long pfn;
	unsigned long undo_pfn;
	struct page *page;
	int nr_isolate_pageblock = 0;

	BUG_ON(!IS_ALIGNED(start_pfn, pageblock_nr_pages));
	BUG_ON(!IS_ALIGNED(end_pfn, pageblock_nr_pages));

	for (pfn = start_pfn;
	     pfn < end_pfn;
	     pfn += pageblock_nr_pages) {
		page = __first_valid_page(pfn, pageblock_nr_pages);
		if (page) {
			if (set_migratetype_isolate(page, migratetype, flags)) {
				undo_pfn = pfn;
				goto undo;
			}
			nr_isolate_pageblock++;
		}
	}
	return nr_isolate_pageblock;
undo:
	for (pfn = start_pfn;
	     pfn < undo_pfn;
	     pfn += pageblock_nr_pages) {
		struct page *page = pfn_to_online_page(pfn);
		if (!page)
			continue;
		unset_migratetype_isolate(page, migratetype);
	}

	return -EBUSY;
}