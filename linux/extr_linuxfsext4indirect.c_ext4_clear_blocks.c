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
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_fsblk_t ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,unsigned long long,unsigned long) ; 
 int EXT4_FREE_BLOCKS_FORGET ; 
 int EXT4_FREE_BLOCKS_METADATA ; 
 int EXT4_FREE_BLOCKS_VALIDATED ; 
 int /*<<< orphan*/  EXT4_INODE_EA_INODE ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_blocks_for_truncate (struct inode*) ; 
 int /*<<< orphan*/  ext4_data_block_valid (int /*<<< orphan*/ ,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *,scalar_t__,unsigned long,int) ; 
 int ext4_handle_dirty_metadata (int /*<<< orphan*/ *,struct inode*,struct buffer_head*) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 int /*<<< orphan*/  ext4_std_error (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_truncate_restart_trans (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ try_to_extend_transaction (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ext4_clear_blocks(handle_t *handle, struct inode *inode,
			     struct buffer_head *bh,
			     ext4_fsblk_t block_to_free,
			     unsigned long count, __le32 *first,
			     __le32 *last)
{
	__le32 *p;
	int	flags = EXT4_FREE_BLOCKS_VALIDATED;
	int	err;

	if (S_ISDIR(inode->i_mode) || S_ISLNK(inode->i_mode) ||
	    ext4_test_inode_flag(inode, EXT4_INODE_EA_INODE))
		flags |= EXT4_FREE_BLOCKS_FORGET | EXT4_FREE_BLOCKS_METADATA;
	else if (ext4_should_journal_data(inode))
		flags |= EXT4_FREE_BLOCKS_FORGET;

	if (!ext4_data_block_valid(EXT4_SB(inode->i_sb), block_to_free,
				   count)) {
		EXT4_ERROR_INODE(inode, "attempt to clear invalid "
				 "blocks %llu len %lu",
				 (unsigned long long) block_to_free, count);
		return 1;
	}

	if (try_to_extend_transaction(handle, inode)) {
		if (bh) {
			BUFFER_TRACE(bh, "call ext4_handle_dirty_metadata");
			err = ext4_handle_dirty_metadata(handle, inode, bh);
			if (unlikely(err))
				goto out_err;
		}
		err = ext4_mark_inode_dirty(handle, inode);
		if (unlikely(err))
			goto out_err;
		err = ext4_truncate_restart_trans(handle, inode,
					ext4_blocks_for_truncate(inode));
		if (unlikely(err))
			goto out_err;
		if (bh) {
			BUFFER_TRACE(bh, "retaking write access");
			err = ext4_journal_get_write_access(handle, bh);
			if (unlikely(err))
				goto out_err;
		}
	}

	for (p = first; p < last; p++)
		*p = 0;

	ext4_free_blocks(handle, inode, NULL, block_to_free, count, flags);
	return 0;
out_err:
	ext4_std_error(inode->i_sb, err);
	return err;
}