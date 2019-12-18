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
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 scalar_t__ buffer_new (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_new (struct buffer_head*) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  write_end_fn (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  zero_user (struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static void ext4_journalled_zero_new_buffers(handle_t *handle,
					    struct page *page,
					    unsigned from, unsigned to)
{
	unsigned int block_start = 0, block_end;
	struct buffer_head *head, *bh;

	bh = head = page_buffers(page);
	do {
		block_end = block_start + bh->b_size;
		if (buffer_new(bh)) {
			if (block_end > from && block_start < to) {
				if (!PageUptodate(page)) {
					unsigned start, size;

					start = max(from, block_start);
					size = min(to, block_end) - start;

					zero_user(page, start, size);
					write_end_fn(handle, bh);
				}
				clear_buffer_new(bh);
			}
		}
		block_start = block_end;
		bh = bh->b_this_page;
	} while (bh != head);
}