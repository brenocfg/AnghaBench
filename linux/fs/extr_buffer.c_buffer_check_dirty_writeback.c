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
struct buffer_head {struct buffer_head* b_this_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 scalar_t__ buffer_locked (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 

void buffer_check_dirty_writeback(struct page *page,
				     bool *dirty, bool *writeback)
{
	struct buffer_head *head, *bh;
	*dirty = false;
	*writeback = false;

	BUG_ON(!PageLocked(page));

	if (!page_has_buffers(page))
		return;

	if (PageWriteback(page))
		*writeback = true;

	head = page_buffers(page);
	bh = head;
	do {
		if (buffer_locked(bh))
			*writeback = true;

		if (buffer_dirty(bh))
			*dirty = true;

		bh = bh->b_this_page;
	} while (bh != head);
}