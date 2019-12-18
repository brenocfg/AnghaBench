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
struct page {TYPE_1__* mapping; } ;
struct extent_buffer {int /*<<< orphan*/  refs; struct page** pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageError (struct page*) ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 int /*<<< orphan*/  PageDirty (struct page*) ; 
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __xa_clear_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 int num_extent_pages (struct extent_buffer*) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  xa_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_unlock_irq (int /*<<< orphan*/ *) ; 

void clear_extent_buffer_dirty(struct extent_buffer *eb)
{
	int i;
	int num_pages;
	struct page *page;

	num_pages = num_extent_pages(eb);

	for (i = 0; i < num_pages; i++) {
		page = eb->pages[i];
		if (!PageDirty(page))
			continue;

		lock_page(page);
		WARN_ON(!PagePrivate(page));

		clear_page_dirty_for_io(page);
		xa_lock_irq(&page->mapping->i_pages);
		if (!PageDirty(page))
			__xa_clear_mark(&page->mapping->i_pages,
					page_index(page), PAGECACHE_TAG_DIRTY);
		xa_unlock_irq(&page->mapping->i_pages);
		ClearPageError(page);
		unlock_page(page);
	}
	WARN_ON(atomic_read(&eb->refs) == 0);
}