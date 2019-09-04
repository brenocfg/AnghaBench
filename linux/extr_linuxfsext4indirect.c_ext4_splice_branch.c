#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ext4_allocation_request {int len; int /*<<< orphan*/  inode; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_3__ {int /*<<< orphan*/  key; int /*<<< orphan*/ * bh; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ Indirect ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  EXT4_FREE_BLOCKS_FORGET ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_free_blocks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int ext4_handle_dirty_metadata (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_mark_inode_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd_debug (int,char*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_splice_branch(handle_t *handle,
			      struct ext4_allocation_request *ar,
			      Indirect *where, int num)
{
	int i;
	int err = 0;
	ext4_fsblk_t current_block;

	/*
	 * If we're splicing into a [td]indirect block (as opposed to the
	 * inode) then we need to get write access to the [td]indirect block
	 * before the splice.
	 */
	if (where->bh) {
		BUFFER_TRACE(where->bh, "get_write_access");
		err = ext4_journal_get_write_access(handle, where->bh);
		if (err)
			goto err_out;
	}
	/* That's it */

	*where->p = where->key;

	/*
	 * Update the host buffer_head or inode to point to more just allocated
	 * direct blocks blocks
	 */
	if (num == 0 && ar->len > 1) {
		current_block = le32_to_cpu(where->key) + 1;
		for (i = 1; i < ar->len; i++)
			*(where->p + i) = cpu_to_le32(current_block++);
	}

	/* We are done with atomic stuff, now do the rest of housekeeping */
	/* had we spliced it onto indirect block? */
	if (where->bh) {
		/*
		 * If we spliced it onto an indirect block, we haven't
		 * altered the inode.  Note however that if it is being spliced
		 * onto an indirect block at the very end of the file (the
		 * file is growing) then we *will* alter the inode to reflect
		 * the new i_size.  But that is not done here - it is done in
		 * generic_commit_write->__mark_inode_dirty->ext4_dirty_inode.
		 */
		jbd_debug(5, "splicing indirect only\n");
		BUFFER_TRACE(where->bh, "call ext4_handle_dirty_metadata");
		err = ext4_handle_dirty_metadata(handle, ar->inode, where->bh);
		if (err)
			goto err_out;
	} else {
		/*
		 * OK, we spliced it into the inode itself on a direct block.
		 */
		ext4_mark_inode_dirty(handle, ar->inode);
		jbd_debug(5, "splicing direct\n");
	}
	return err;

err_out:
	for (i = 1; i <= num; i++) {
		/*
		 * branch[i].bh is newly allocated, so there is no
		 * need to revoke the block, which is why we don't
		 * need to set EXT4_FREE_BLOCKS_METADATA.
		 */
		ext4_free_blocks(handle, ar->inode, where[i].bh, 0, 1,
				 EXT4_FREE_BLOCKS_FORGET);
	}
	ext4_free_blocks(handle, ar->inode, NULL, le32_to_cpu(where[num].key),
			 ar->len, 0);

	return err;
}