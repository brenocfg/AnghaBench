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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct file {int dummy; } ;
struct ext4_iloc {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_HT_INODE ; 
 int /*<<< orphan*/  EXT4_INODE_VERITY ; 
 int /*<<< orphan*/  EXT4_STATE_VERITY_IN_PROGRESS ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_clear_inode_state (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int ext4_mark_iloc_dirty (int /*<<< orphan*/ *,struct inode*,struct ext4_iloc*) ; 
 int ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 int ext4_reserve_inode_write (int /*<<< orphan*/ *,struct inode*,struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  ext4_truncate (struct inode*) ; 
 int ext4_write_verity_descriptor (struct inode*,void const*,size_t,int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 int filemap_write_and_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_end_enable_verity(struct file *filp, const void *desc,
				  size_t desc_size, u64 merkle_tree_size)
{
	struct inode *inode = file_inode(filp);
	const int credits = 2; /* superblock and inode for ext4_orphan_del() */
	handle_t *handle;
	int err = 0;
	int err2;

	if (desc != NULL) {
		/* Succeeded; write the verity descriptor. */
		err = ext4_write_verity_descriptor(inode, desc, desc_size,
						   merkle_tree_size);

		/* Write all pages before clearing VERITY_IN_PROGRESS. */
		if (!err)
			err = filemap_write_and_wait(inode->i_mapping);
	}

	/* If we failed, truncate anything we wrote past i_size. */
	if (desc == NULL || err)
		ext4_truncate(inode);

	/*
	 * We must always clean up by clearing EXT4_STATE_VERITY_IN_PROGRESS and
	 * deleting the inode from the orphan list, even if something failed.
	 * If everything succeeded, we'll also set the verity bit in the same
	 * transaction.
	 */

	ext4_clear_inode_state(inode, EXT4_STATE_VERITY_IN_PROGRESS);

	handle = ext4_journal_start(inode, EXT4_HT_INODE, credits);
	if (IS_ERR(handle)) {
		ext4_orphan_del(NULL, inode);
		return PTR_ERR(handle);
	}

	err2 = ext4_orphan_del(handle, inode);
	if (err2)
		goto out_stop;

	if (desc != NULL && !err) {
		struct ext4_iloc iloc;

		err = ext4_reserve_inode_write(handle, inode, &iloc);
		if (err)
			goto out_stop;
		ext4_set_inode_flag(inode, EXT4_INODE_VERITY);
		ext4_set_inode_flags(inode);
		err = ext4_mark_iloc_dirty(handle, inode, &iloc);
	}
out_stop:
	ext4_journal_stop(handle);
	return err ?: err2;
}