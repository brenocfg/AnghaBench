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
struct buffer_head {unsigned int b_size; struct buffer_head* b_this_page; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int stub1 (int /*<<< orphan*/ *,struct buffer_head*) ; 

int walk_page_buffers(	handle_t *handle,
			struct buffer_head *head,
			unsigned from,
			unsigned to,
			int *partial,
			int (*fn)(	handle_t *handle,
					struct buffer_head *bh))
{
	struct buffer_head *bh;
	unsigned block_start, block_end;
	unsigned blocksize = head->b_size;
	int err, ret = 0;
	struct buffer_head *next;

	for (	bh = head, block_start = 0;
		ret == 0 && (bh != head || !block_start);
	    	block_start = block_end, bh = next)
	{
		next = bh->b_this_page;
		block_end = block_start + blocksize;
		if (block_end <= from || block_start >= to) {
			if (partial && !buffer_uptodate(bh))
				*partial = 1;
			continue;
		}
		err = (*fn)(handle, bh);
		if (!ret)
			ret = err;
	}
	return ret;
}