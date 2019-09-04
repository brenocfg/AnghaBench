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
struct pagevec {struct page** pages; } ;
struct page {int dummy; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ pgoff_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int /*<<< orphan*/  PAGECACHE_TAG_WRITEBACK ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  pagevec_init (struct pagevec*) ; 
 int pagevec_lookup_range_tag (struct pagevec*,struct address_space*,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagevec_release (struct pagevec*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

__attribute__((used)) static void __filemap_fdatawait_range(struct address_space *mapping,
				     loff_t start_byte, loff_t end_byte)
{
	pgoff_t index = start_byte >> PAGE_SHIFT;
	pgoff_t end = end_byte >> PAGE_SHIFT;
	struct pagevec pvec;
	int nr_pages;

	if (end_byte < start_byte)
		return;

	pagevec_init(&pvec);
	while (index <= end) {
		unsigned i;

		nr_pages = pagevec_lookup_range_tag(&pvec, mapping, &index,
				end, PAGECACHE_TAG_WRITEBACK);
		if (!nr_pages)
			break;

		for (i = 0; i < nr_pages; i++) {
			struct page *page = pvec.pages[i];

			wait_on_page_writeback(page);
			ClearPageError(page);
		}
		pagevec_release(&pvec);
		cond_resched();
	}
}