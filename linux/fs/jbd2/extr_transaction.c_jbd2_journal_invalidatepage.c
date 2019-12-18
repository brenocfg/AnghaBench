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
struct buffer_head {unsigned int b_size; struct buffer_head* b_this_page; } ;
typedef  int /*<<< orphan*/  journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  J_ASSERT (int) ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int journal_unmap_buffer (int /*<<< orphan*/ *,struct buffer_head*,int) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 scalar_t__ try_to_free_buffers (struct page*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

int jbd2_journal_invalidatepage(journal_t *journal,
				struct page *page,
				unsigned int offset,
				unsigned int length)
{
	struct buffer_head *head, *bh, *next;
	unsigned int stop = offset + length;
	unsigned int curr_off = 0;
	int partial_page = (offset || length < PAGE_SIZE);
	int may_free = 1;
	int ret = 0;

	if (!PageLocked(page))
		BUG();
	if (!page_has_buffers(page))
		return 0;

	BUG_ON(stop > PAGE_SIZE || stop < length);

	/* We will potentially be playing with lists other than just the
	 * data lists (especially for journaled data mode), so be
	 * cautious in our locking. */

	head = bh = page_buffers(page);
	do {
		unsigned int next_off = curr_off + bh->b_size;
		next = bh->b_this_page;

		if (next_off > stop)
			return 0;

		if (offset <= curr_off) {
			/* This block is wholly outside the truncation point */
			lock_buffer(bh);
			ret = journal_unmap_buffer(journal, bh, partial_page);
			unlock_buffer(bh);
			if (ret < 0)
				return ret;
			may_free &= ret;
		}
		curr_off = next_off;
		bh = next;

	} while (bh != head);

	if (!partial_page) {
		if (may_free && try_to_free_buffers(page))
			J_ASSERT(!page_has_buffers(page));
	}
	return 0;
}