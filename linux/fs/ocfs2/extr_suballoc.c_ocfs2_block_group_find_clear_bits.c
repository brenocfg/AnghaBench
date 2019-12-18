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
typedef  int u16 ;
struct ocfs2_super {int dummy; } ;
struct ocfs2_suballoc_result {int sr_bit_offset; int sr_bits; } ;
struct ocfs2_group_desc {void* bg_bitmap; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_GROUP_DESC (struct ocfs2_group_desc*) ; 
 int ocfs2_find_next_zero_bit (void*,unsigned int,int) ; 
 int /*<<< orphan*/  ocfs2_test_bg_bit_allocatable (struct buffer_head*,int) ; 

__attribute__((used)) static int ocfs2_block_group_find_clear_bits(struct ocfs2_super *osb,
					     struct buffer_head *bg_bh,
					     unsigned int bits_wanted,
					     unsigned int total_bits,
					     struct ocfs2_suballoc_result *res)
{
	void *bitmap;
	u16 best_offset, best_size;
	int offset, start, found, status = 0;
	struct ocfs2_group_desc *bg = (struct ocfs2_group_desc *) bg_bh->b_data;

	/* Callers got this descriptor from
	 * ocfs2_read_group_descriptor().  Any corruption is a code bug. */
	BUG_ON(!OCFS2_IS_VALID_GROUP_DESC(bg));

	found = start = best_offset = best_size = 0;
	bitmap = bg->bg_bitmap;

	while((offset = ocfs2_find_next_zero_bit(bitmap, total_bits, start)) != -1) {
		if (offset == total_bits)
			break;

		if (!ocfs2_test_bg_bit_allocatable(bg_bh, offset)) {
			/* We found a zero, but we can't use it as it
			 * hasn't been put to disk yet! */
			found = 0;
			start = offset + 1;
		} else if (offset == start) {
			/* we found a zero */
			found++;
			/* move start to the next bit to test */
			start++;
		} else {
			/* got a zero after some ones */
			found = 1;
			start = offset + 1;
		}
		if (found > best_size) {
			best_size = found;
			best_offset = start - found;
		}
		/* we got everything we needed */
		if (found == bits_wanted) {
			/* mlog(0, "Found it all!\n"); */
			break;
		}
	}

	if (best_size) {
		res->sr_bit_offset = best_offset;
		res->sr_bits = best_size;
	} else {
		status = -ENOSPC;
		/* No error log here -- see the comment above
		 * ocfs2_test_bg_bit_allocatable */
	}

	return status;
}