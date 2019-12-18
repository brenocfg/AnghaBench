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
struct inode {int dummy; } ;
struct ext4_iloc {int /*<<< orphan*/ * bh; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_HT_WRITE_PAGE ; 
 int /*<<< orphan*/  EXT4_STATE_MAY_INLINE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_convert_inline_data_nolock (int /*<<< orphan*/ *,struct inode*,struct ext4_iloc*) ; 
 int ext4_get_inode_loc (struct inode*,struct ext4_iloc*) ; 
 scalar_t__ ext4_has_inline_data (struct inode*) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_write_lock_xattr (struct inode*,int*) ; 
 int /*<<< orphan*/  ext4_write_unlock_xattr (struct inode*,int*) ; 
 int ext4_writepage_trans_blocks (struct inode*) ; 

int ext4_convert_inline_data(struct inode *inode)
{
	int error, needed_blocks, no_expand;
	handle_t *handle;
	struct ext4_iloc iloc;

	if (!ext4_has_inline_data(inode)) {
		ext4_clear_inode_state(inode, EXT4_STATE_MAY_INLINE_DATA);
		return 0;
	}

	needed_blocks = ext4_writepage_trans_blocks(inode);

	iloc.bh = NULL;
	error = ext4_get_inode_loc(inode, &iloc);
	if (error)
		return error;

	handle = ext4_journal_start(inode, EXT4_HT_WRITE_PAGE, needed_blocks);
	if (IS_ERR(handle)) {
		error = PTR_ERR(handle);
		goto out_free;
	}

	ext4_write_lock_xattr(inode, &no_expand);
	if (ext4_has_inline_data(inode))
		error = ext4_convert_inline_data_nolock(handle, inode, &iloc);
	ext4_write_unlock_xattr(inode, &no_expand);
	ext4_journal_stop(handle);
out_free:
	brelse(iloc.bh);
	return error;
}