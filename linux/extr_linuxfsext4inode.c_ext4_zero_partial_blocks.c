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
struct super_block {int s_blocksize; int s_blocksize_bits; } ;
struct inode {struct address_space* i_mapping; struct super_block* i_sb; } ;
struct address_space {int dummy; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_fsblk_t ;

/* Variables and functions */
 int ext4_block_zero_page_range (int /*<<< orphan*/ *,struct address_space*,int,unsigned int) ; 

int ext4_zero_partial_blocks(handle_t *handle, struct inode *inode,
			     loff_t lstart, loff_t length)
{
	struct super_block *sb = inode->i_sb;
	struct address_space *mapping = inode->i_mapping;
	unsigned partial_start, partial_end;
	ext4_fsblk_t start, end;
	loff_t byte_end = (lstart + length - 1);
	int err = 0;

	partial_start = lstart & (sb->s_blocksize - 1);
	partial_end = byte_end & (sb->s_blocksize - 1);

	start = lstart >> sb->s_blocksize_bits;
	end = byte_end >> sb->s_blocksize_bits;

	/* Handle partial zero within the single block */
	if (start == end &&
	    (partial_start || (partial_end != sb->s_blocksize - 1))) {
		err = ext4_block_zero_page_range(handle, mapping,
						 lstart, length);
		return err;
	}
	/* Handle partial zero out on the start of the range */
	if (partial_start) {
		err = ext4_block_zero_page_range(handle, mapping,
						 lstart, sb->s_blocksize);
		if (err)
			return err;
	}
	/* Handle partial zero out on the end of the range */
	if (partial_end != sb->s_blocksize - 1)
		err = ext4_block_zero_page_range(handle, mapping,
						 byte_end - partial_end,
						 partial_end + 1);
	return err;
}