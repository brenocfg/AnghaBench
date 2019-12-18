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
struct extent_buffer {struct page** pages; int /*<<< orphan*/  bflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  EXTENT_BUFFER_UPTODATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int num_extent_pages (struct extent_buffer*) ; 

void clear_extent_buffer_uptodate(struct extent_buffer *eb)
{
	int i;
	struct page *page;
	int num_pages;

	clear_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags);
	num_pages = num_extent_pages(eb);
	for (i = 0; i < num_pages; i++) {
		page = eb->pages[i];
		if (page)
			ClearPageUptodate(page);
	}
}