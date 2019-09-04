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
struct inode {int i_blkbits; int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int b_size; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int DIO_MAX_BLOCKS ; 
 int ENOSPC ; 
 int /*<<< orphan*/  EXT4_HT_MAP_BLOCKS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int _ext4_get_block (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,int) ; 
 int ext4_chunk_trans_blocks (struct inode*,int) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_should_retry_alloc (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ext4_get_block_trans(struct inode *inode, sector_t iblock,
				struct buffer_head *bh_result, int flags)
{
	int dio_credits;
	handle_t *handle;
	int retries = 0;
	int ret;

	/* Trim mapping request to maximum we can map at once for DIO */
	if (bh_result->b_size >> inode->i_blkbits > DIO_MAX_BLOCKS)
		bh_result->b_size = DIO_MAX_BLOCKS << inode->i_blkbits;
	dio_credits = ext4_chunk_trans_blocks(inode,
				      bh_result->b_size >> inode->i_blkbits);
retry:
	handle = ext4_journal_start(inode, EXT4_HT_MAP_BLOCKS, dio_credits);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	ret = _ext4_get_block(inode, iblock, bh_result, flags);
	ext4_journal_stop(handle);

	if (ret == -ENOSPC && ext4_should_retry_alloc(inode->i_sb, &retries))
		goto retry;
	return ret;
}