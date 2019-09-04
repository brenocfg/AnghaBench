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
struct writeback_control {scalar_t__ sync_mode; } ;
struct page {int dummy; } ;
struct buffer_head {struct buffer_head* b_this_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int PageWriteback (struct page*) ; 
 int REQ_META ; 
 int /*<<< orphan*/  REQ_OP_WRITE ; 
 int REQ_PRIO ; 
 scalar_t__ WB_SYNC_NONE ; 
 scalar_t__ buffer_async_write (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_async_write (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,int,struct buffer_head*) ; 
 scalar_t__ test_clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  trylock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int wbc_to_write_flags (struct writeback_control*) ; 

__attribute__((used)) static int gfs2_aspace_writepage(struct page *page, struct writeback_control *wbc)
{
	struct buffer_head *bh, *head;
	int nr_underway = 0;
	int write_flags = REQ_META | REQ_PRIO | wbc_to_write_flags(wbc);

	BUG_ON(!PageLocked(page));
	BUG_ON(!page_has_buffers(page));

	head = page_buffers(page);
	bh = head;

	do {
		if (!buffer_mapped(bh))
			continue;
		/*
		 * If it's a fully non-blocking write attempt and we cannot
		 * lock the buffer then redirty the page.  Note that this can
		 * potentially cause a busy-wait loop from flusher thread and kswapd
		 * activity, but those code paths have their own higher-level
		 * throttling.
		 */
		if (wbc->sync_mode != WB_SYNC_NONE) {
			lock_buffer(bh);
		} else if (!trylock_buffer(bh)) {
			redirty_page_for_writepage(wbc, page);
			continue;
		}
		if (test_clear_buffer_dirty(bh)) {
			mark_buffer_async_write(bh);
		} else {
			unlock_buffer(bh);
		}
	} while ((bh = bh->b_this_page) != head);

	/*
	 * The page and its buffers are protected by PageWriteback(), so we can
	 * drop the bh refcounts early.
	 */
	BUG_ON(PageWriteback(page));
	set_page_writeback(page);

	do {
		struct buffer_head *next = bh->b_this_page;
		if (buffer_async_write(bh)) {
			submit_bh(REQ_OP_WRITE, write_flags, bh);
			nr_underway++;
		}
		bh = next;
	} while (bh != head);
	unlock_page(page);

	if (nr_underway == 0)
		end_page_writeback(page);

	return 0;
}