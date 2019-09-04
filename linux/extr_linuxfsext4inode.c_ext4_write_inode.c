#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {scalar_t__ sync_mode; scalar_t__ for_sync; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_iloc {TYPE_1__* bh; } ;
struct TYPE_12__ {int /*<<< orphan*/  i_sync_tid; } ;
struct TYPE_11__ {int flags; } ;
struct TYPE_10__ {scalar_t__ s_journal; } ;
struct TYPE_9__ {int /*<<< orphan*/  b_blocknr; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE_BLOCK (struct inode*,int /*<<< orphan*/ ,char*) ; 
 TYPE_8__* EXT4_I (struct inode*) ; 
 TYPE_2__* EXT4_SB (int /*<<< orphan*/ ) ; 
 int PF_MEMALLOC ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ WB_SYNC_ALL ; 
 int __ext4_get_inode_loc (struct inode*,struct ext4_iloc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (TYPE_1__*) ; 
 scalar_t__ buffer_req (TYPE_1__*) ; 
 int /*<<< orphan*/  buffer_uptodate (TYPE_1__*) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  dump_stack () ; 
 int /*<<< orphan*/  ext4_forced_shutdown (TYPE_2__*) ; 
 scalar_t__ ext4_journal_current_handle () ; 
 int jbd2_complete_transaction (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jbd_debug (int,char*) ; 
 scalar_t__ sb_rdonly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_dirty_buffer (TYPE_1__*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int ext4_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	int err;

	if (WARN_ON_ONCE(current->flags & PF_MEMALLOC) ||
	    sb_rdonly(inode->i_sb))
		return 0;

	if (unlikely(ext4_forced_shutdown(EXT4_SB(inode->i_sb))))
		return -EIO;

	if (EXT4_SB(inode->i_sb)->s_journal) {
		if (ext4_journal_current_handle()) {
			jbd_debug(1, "called recursively, non-PF_MEMALLOC!\n");
			dump_stack();
			return -EIO;
		}

		/*
		 * No need to force transaction in WB_SYNC_NONE mode. Also
		 * ext4_sync_fs() will force the commit after everything is
		 * written.
		 */
		if (wbc->sync_mode != WB_SYNC_ALL || wbc->for_sync)
			return 0;

		err = jbd2_complete_transaction(EXT4_SB(inode->i_sb)->s_journal,
						EXT4_I(inode)->i_sync_tid);
	} else {
		struct ext4_iloc iloc;

		err = __ext4_get_inode_loc(inode, &iloc, 0);
		if (err)
			return err;
		/*
		 * sync(2) will flush the whole buffer cache. No need to do
		 * it here separately for each inode.
		 */
		if (wbc->sync_mode == WB_SYNC_ALL && !wbc->for_sync)
			sync_dirty_buffer(iloc.bh);
		if (buffer_req(iloc.bh) && !buffer_uptodate(iloc.bh)) {
			EXT4_ERROR_INODE_BLOCK(inode, iloc.bh->b_blocknr,
					 "IO error syncing inode");
			err = -EIO;
		}
		brelse(iloc.bh);
	}
	return err;
}