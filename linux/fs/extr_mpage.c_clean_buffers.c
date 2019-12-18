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
 scalar_t__ PageUptodate (struct page*) ; 
 scalar_t__ buffer_heads_over_limit ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  try_to_free_buffers (struct page*) ; 

__attribute__((used)) static void clean_buffers(struct page *page, unsigned first_unmapped)
{
	unsigned buffer_counter = 0;
	struct buffer_head *bh, *head;
	if (!page_has_buffers(page))
		return;
	head = page_buffers(page);
	bh = head;

	do {
		if (buffer_counter++ == first_unmapped)
			break;
		clear_buffer_dirty(bh);
		bh = bh->b_this_page;
	} while (bh != head);

	/*
	 * we cannot drop the bh if the page is not uptodate or a concurrent
	 * readpage would fail to serialize with the bh and it would read from
	 * disk before we reach the platter.
	 */
	if (buffer_heads_over_limit && PageUptodate(page))
		try_to_free_buffers(page);
}