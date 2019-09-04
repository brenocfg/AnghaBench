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
struct nilfs_write_info {scalar_t__ nr_vecs; scalar_t__ end; scalar_t__ bio; scalar_t__ blocknr; int /*<<< orphan*/  nilfs; } ;
struct nilfs_segment_buffer {int dummy; } ;
struct buffer_head {int b_size; int /*<<< orphan*/  b_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bh_offset (struct buffer_head*) ; 
 int bio_add_page (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ nilfs_alloc_seg_bio (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int nilfs_segbuf_submit_bio (struct nilfs_segment_buffer*,struct nilfs_write_info*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nilfs_segbuf_submit_bh(struct nilfs_segment_buffer *segbuf,
				  struct nilfs_write_info *wi,
				  struct buffer_head *bh, int mode)
{
	int len, err;

	BUG_ON(wi->nr_vecs <= 0);
 repeat:
	if (!wi->bio) {
		wi->bio = nilfs_alloc_seg_bio(wi->nilfs, wi->blocknr + wi->end,
					      wi->nr_vecs);
		if (unlikely(!wi->bio))
			return -ENOMEM;
	}

	len = bio_add_page(wi->bio, bh->b_page, bh->b_size, bh_offset(bh));
	if (len == bh->b_size) {
		wi->end++;
		return 0;
	}
	/* bio is FULL */
	err = nilfs_segbuf_submit_bio(segbuf, wi, mode, 0);
	/* never submit current bh */
	if (likely(!err))
		goto repeat;
	return err;
}