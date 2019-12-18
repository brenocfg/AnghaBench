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
struct ext4_iloc {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOSPC ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  EXT4_DATA_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_STATE_NO_EXPAND ; 
 int __ext4_expand_extra_isize (struct inode*,unsigned int,struct ext4_iloc*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ ext4_handle_valid (int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_write_trylock_xattr (struct inode*,int*) ; 
 int /*<<< orphan*/  ext4_write_unlock_xattr (struct inode*,int*) ; 
 scalar_t__ jbd2_journal_extend (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_try_to_expand_extra_isize(struct inode *inode,
					  unsigned int new_extra_isize,
					  struct ext4_iloc iloc,
					  handle_t *handle)
{
	int no_expand;
	int error;

	if (ext4_test_inode_state(inode, EXT4_STATE_NO_EXPAND))
		return -EOVERFLOW;

	/*
	 * In nojournal mode, we can immediately attempt to expand
	 * the inode.  When journaled, we first need to obtain extra
	 * buffer credits since we may write into the EA block
	 * with this same handle. If journal_extend fails, then it will
	 * only result in a minor loss of functionality for that inode.
	 * If this is felt to be critical, then e2fsck should be run to
	 * force a large enough s_min_extra_isize.
	 */
	if (ext4_handle_valid(handle) &&
	    jbd2_journal_extend(handle,
				EXT4_DATA_TRANS_BLOCKS(inode->i_sb)) != 0)
		return -ENOSPC;

	if (ext4_write_trylock_xattr(inode, &no_expand) == 0)
		return -EBUSY;

	error = __ext4_expand_extra_isize(inode, new_extra_isize, &iloc,
					  handle, &no_expand);
	ext4_write_unlock_xattr(inode, &no_expand);

	return error;
}