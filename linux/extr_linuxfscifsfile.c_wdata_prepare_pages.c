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
struct writeback_control {scalar_t__ sync_mode; int /*<<< orphan*/  range_cyclic; } ;
struct page {scalar_t__ index; struct address_space* mapping; } ;
struct cifs_writedata {struct page** pages; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 scalar_t__ PageWriteback (struct page*) ; 
 scalar_t__ WB_SYNC_NONE ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 scalar_t__ page_offset (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

__attribute__((used)) static unsigned int
wdata_prepare_pages(struct cifs_writedata *wdata, unsigned int found_pages,
		    struct address_space *mapping,
		    struct writeback_control *wbc,
		    pgoff_t end, pgoff_t *index, pgoff_t *next, bool *done)
{
	unsigned int nr_pages = 0, i;
	struct page *page;

	for (i = 0; i < found_pages; i++) {
		page = wdata->pages[i];
		/*
		 * At this point we hold neither the i_pages lock nor the
		 * page lock: the page may be truncated or invalidated
		 * (changing page->mapping to NULL), or even swizzled
		 * back from swapper_space to tmpfs file mapping
		 */

		if (nr_pages == 0)
			lock_page(page);
		else if (!trylock_page(page))
			break;

		if (unlikely(page->mapping != mapping)) {
			unlock_page(page);
			break;
		}

		if (!wbc->range_cyclic && page->index > end) {
			*done = true;
			unlock_page(page);
			break;
		}

		if (*next && (page->index != *next)) {
			/* Not next consecutive page */
			unlock_page(page);
			break;
		}

		if (wbc->sync_mode != WB_SYNC_NONE)
			wait_on_page_writeback(page);

		if (PageWriteback(page) ||
				!clear_page_dirty_for_io(page)) {
			unlock_page(page);
			break;
		}

		/*
		 * This actually clears the dirty bit in the radix tree.
		 * See cifs_writepage() for more commentary.
		 */
		set_page_writeback(page);
		if (page_offset(page) >= i_size_read(mapping->host)) {
			*done = true;
			unlock_page(page);
			end_page_writeback(page);
			break;
		}

		wdata->pages[i] = page;
		*next = page->index + 1;
		++nr_pages;
	}

	/* reset index to refind any pages skipped */
	if (nr_pages == 0)
		*index = wdata->pages[0]->index + 1;

	/* put any pages we aren't going to use */
	for (i = nr_pages; i < found_pages; i++) {
		put_page(wdata->pages[i]);
		wdata->pages[i] = NULL;
	}

	return nr_pages;
}