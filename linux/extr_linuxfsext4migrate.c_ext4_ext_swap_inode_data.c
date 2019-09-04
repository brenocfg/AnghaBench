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
struct inode {int /*<<< orphan*/  i_lock; scalar_t__ i_blocks; } ;
struct ext4_inode_info {int /*<<< orphan*/  i_data_sem; int /*<<< orphan*/ * i_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EAGAIN ; 
 size_t EXT4_DIND_BLOCK ; 
 struct ext4_inode_info* EXT4_I (struct inode*) ; 
 size_t EXT4_IND_BLOCK ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 int /*<<< orphan*/  EXT4_STATE_EXT_MIGRATE ; 
 size_t EXT4_TIND_BLOCK ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int ext4_journal_extend (int /*<<< orphan*/ *,int) ; 
 int ext4_journal_restart (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_test_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int free_ind_block (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext4_ext_swap_inode_data(handle_t *handle, struct inode *inode,
						struct inode *tmp_inode)
{
	int retval;
	__le32	i_data[3];
	struct ext4_inode_info *ei = EXT4_I(inode);
	struct ext4_inode_info *tmp_ei = EXT4_I(tmp_inode);

	/*
	 * One credit accounted for writing the
	 * i_data field of the original inode
	 */
	retval = ext4_journal_extend(handle, 1);
	if (retval) {
		retval = ext4_journal_restart(handle, 1);
		if (retval)
			goto err_out;
	}

	i_data[0] = ei->i_data[EXT4_IND_BLOCK];
	i_data[1] = ei->i_data[EXT4_DIND_BLOCK];
	i_data[2] = ei->i_data[EXT4_TIND_BLOCK];

	down_write(&EXT4_I(inode)->i_data_sem);
	/*
	 * if EXT4_STATE_EXT_MIGRATE is cleared a block allocation
	 * happened after we started the migrate. We need to
	 * fail the migrate
	 */
	if (!ext4_test_inode_state(inode, EXT4_STATE_EXT_MIGRATE)) {
		retval = -EAGAIN;
		up_write(&EXT4_I(inode)->i_data_sem);
		goto err_out;
	} else
		ext4_clear_inode_state(inode, EXT4_STATE_EXT_MIGRATE);
	/*
	 * We have the extent map build with the tmp inode.
	 * Now copy the i_data across
	 */
	ext4_set_inode_flag(inode, EXT4_INODE_EXTENTS);
	memcpy(ei->i_data, tmp_ei->i_data, sizeof(ei->i_data));

	/*
	 * Update i_blocks with the new blocks that got
	 * allocated while adding extents for extent index
	 * blocks.
	 *
	 * While converting to extents we need not
	 * update the original inode i_blocks for extent blocks
	 * via quota APIs. The quota update happened via tmp_inode already.
	 */
	spin_lock(&inode->i_lock);
	inode->i_blocks += tmp_inode->i_blocks;
	spin_unlock(&inode->i_lock);
	up_write(&EXT4_I(inode)->i_data_sem);

	/*
	 * We mark the inode dirty after, because we decrement the
	 * i_blocks when freeing the indirect meta-data blocks
	 */
	retval = free_ind_block(handle, inode, i_data);
	ext4_mark_inode_dirty(handle, inode);

err_out:
	return retval;
}