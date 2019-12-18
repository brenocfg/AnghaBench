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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_iloc {int /*<<< orphan*/  bh; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (int /*<<< orphan*/ ,char*) ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  EXT4_DATA_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_HT_INODE ; 
 int /*<<< orphan*/  EXT4_STATE_NO_EXPAND ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int __ext4_expand_extra_isize (struct inode*,unsigned int,struct ext4_iloc*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int ext4_mark_iloc_dirty (int /*<<< orphan*/ *,struct inode*,struct ext4_iloc*) ; 
 scalar_t__ ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_write_lock_xattr (struct inode*,int*) ; 
 int /*<<< orphan*/  ext4_write_unlock_xattr (struct inode*,int*) ; 

int ext4_expand_extra_isize(struct inode *inode,
			    unsigned int new_extra_isize,
			    struct ext4_iloc *iloc)
{
	handle_t *handle;
	int no_expand;
	int error, rc;

	if (ext4_test_inode_state(inode, EXT4_STATE_NO_EXPAND)) {
		brelse(iloc->bh);
		return -EOVERFLOW;
	}

	handle = ext4_journal_start(inode, EXT4_HT_INODE,
				    EXT4_DATA_TRANS_BLOCKS(inode->i_sb));
	if (IS_ERR(handle)) {
		error = PTR_ERR(handle);
		brelse(iloc->bh);
		return error;
	}

	ext4_write_lock_xattr(inode, &no_expand);

	BUFFER_TRACE(iloc->bh, "get_write_access");
	error = ext4_journal_get_write_access(handle, iloc->bh);
	if (error) {
		brelse(iloc->bh);
		goto out_stop;
	}

	error = __ext4_expand_extra_isize(inode, new_extra_isize, iloc,
					  handle, &no_expand);

	rc = ext4_mark_iloc_dirty(handle, inode, iloc);
	if (!error)
		error = rc;

	ext4_write_unlock_xattr(inode, &no_expand);
out_stop:
	ext4_journal_stop(handle);
	return error;
}