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
 int EIO ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_I_VERSION (struct inode*) ; 
 int ext4_do_update_inode (int /*<<< orphan*/ *,struct inode*,struct ext4_iloc*) ; 
 int /*<<< orphan*/  ext4_forced_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 
 int /*<<< orphan*/  put_bh (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int ext4_mark_iloc_dirty(handle_t *handle,
			 struct inode *inode, struct ext4_iloc *iloc)
{
	int err = 0;

	if (unlikely(ext4_forced_shutdown(EXT4_SB(inode->i_sb)))) {
		put_bh(iloc->bh);
		return -EIO;
	}
	if (IS_I_VERSION(inode))
		inode_inc_iversion(inode);

	/* the do_update_inode consumes one bh->b_count */
	get_bh(iloc->bh);

	/* ext4_do_update_inode() does jbd2_journal_dirty_metadata */
	err = ext4_do_update_inode(handle, inode, iloc);
	put_bh(iloc->bh);
	return err;
}