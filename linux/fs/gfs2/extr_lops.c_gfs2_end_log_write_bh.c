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
struct gfs2_sbd {int dummy; } ;
struct buffer_head {scalar_t__ b_size; struct buffer_head* b_this_page; } ;
struct bio_vec {unsigned int bv_len; scalar_t__ bv_offset; struct page* bv_page; } ;
typedef  scalar_t__ blk_status_t ;

/* Variables and functions */
 scalar_t__ bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_write_io_error (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static void gfs2_end_log_write_bh(struct gfs2_sbd *sdp,
				  struct bio_vec *bvec,
				  blk_status_t error)
{
	struct buffer_head *bh, *next;
	struct page *page = bvec->bv_page;
	unsigned size;

	bh = page_buffers(page);
	size = bvec->bv_len;
	while (bh_offset(bh) < bvec->bv_offset)
		bh = bh->b_this_page;
	do {
		if (error)
			mark_buffer_write_io_error(bh);
		unlock_buffer(bh);
		next = bh->b_this_page;
		size -= bh->b_size;
		brelse(bh);
		bh = next;
	} while(bh && size);
}