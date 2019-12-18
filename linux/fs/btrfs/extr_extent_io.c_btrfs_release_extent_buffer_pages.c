#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {unsigned long private; TYPE_1__* mapping; } ;
struct extent_buffer {int /*<<< orphan*/  bflags; struct page** pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  private_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  EXTENT_BUFFER_DIRTY ; 
 int /*<<< orphan*/  EXTENT_BUFFER_UNMAPPED ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 scalar_t__ PagePrivate (struct page*) ; 
 int /*<<< orphan*/  PageWriteback (struct page*) ; 
 int /*<<< orphan*/  extent_buffer_under_io (struct extent_buffer*) ; 
 int num_extent_pages (struct extent_buffer*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfs_release_extent_buffer_pages(struct extent_buffer *eb)
{
	int i;
	int num_pages;
	int mapped = !test_bit(EXTENT_BUFFER_UNMAPPED, &eb->bflags);

	BUG_ON(extent_buffer_under_io(eb));

	num_pages = num_extent_pages(eb);
	for (i = 0; i < num_pages; i++) {
		struct page *page = eb->pages[i];

		if (!page)
			continue;
		if (mapped)
			spin_lock(&page->mapping->private_lock);
		/*
		 * We do this since we'll remove the pages after we've
		 * removed the eb from the radix tree, so we could race
		 * and have this page now attached to the new eb.  So
		 * only clear page_private if it's still connected to
		 * this eb.
		 */
		if (PagePrivate(page) &&
		    page->private == (unsigned long)eb) {
			BUG_ON(test_bit(EXTENT_BUFFER_DIRTY, &eb->bflags));
			BUG_ON(PageDirty(page));
			BUG_ON(PageWriteback(page));
			/*
			 * We need to make sure we haven't be attached
			 * to a new eb.
			 */
			ClearPagePrivate(page);
			set_page_private(page, 0);
			/* One for the page private */
			put_page(page);
		}

		if (mapped)
			spin_unlock(&page->mapping->private_lock);

		/* One for when we allocated the page */
		put_page(page);
	}
}