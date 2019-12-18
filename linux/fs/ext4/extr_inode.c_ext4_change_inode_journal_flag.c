#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mapping; } ;
struct ext4_sb_info {int /*<<< orphan*/  s_journal_flag_rwsem; } ;
typedef  int /*<<< orphan*/  journal_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_mmap_sem; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  EXT4_HT_INODE ; 
 TYPE_1__* EXT4_I (struct inode*) ; 
 int /*<<< orphan*/  EXT4_INODE_JOURNAL_DATA ; 
 int /*<<< orphan*/ * EXT4_JOURNAL (struct inode*) ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_set_aops (struct inode*) ; 
 int /*<<< orphan*/  ext4_set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_std_error (int /*<<< orphan*/ ,int) ; 
 int filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 scalar_t__ is_journal_aborted (int /*<<< orphan*/ *) ; 
 int jbd2_journal_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_lock_updates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jbd2_journal_unlock_updates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ext4_change_inode_journal_flag(struct inode *inode, int val)
{
	journal_t *journal;
	handle_t *handle;
	int err;
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

	/*
	 * We have to be very careful here: changing a data block's
	 * journaling status dynamically is dangerous.  If we write a
	 * data block to the journal, change the status and then delete
	 * that block, we risk forgetting to revoke the old log record
	 * from the journal and so a subsequent replay can corrupt data.
	 * So, first we make sure that the journal is empty and that
	 * nobody is changing anything.
	 */

	journal = EXT4_JOURNAL(inode);
	if (!journal)
		return 0;
	if (is_journal_aborted(journal))
		return -EROFS;

	/* Wait for all existing dio workers */
	inode_dio_wait(inode);

	/*
	 * Before flushing the journal and switching inode's aops, we have
	 * to flush all dirty data the inode has. There can be outstanding
	 * delayed allocations, there can be unwritten extents created by
	 * fallocate or buffered writes in dioread_nolock mode covered by
	 * dirty data which can be converted only after flushing the dirty
	 * data (and journalled aops don't know how to handle these cases).
	 */
	if (val) {
		down_write(&EXT4_I(inode)->i_mmap_sem);
		err = filemap_write_and_wait(inode->i_mapping);
		if (err < 0) {
			up_write(&EXT4_I(inode)->i_mmap_sem);
			return err;
		}
	}

	percpu_down_write(&sbi->s_journal_flag_rwsem);
	jbd2_journal_lock_updates(journal);

	/*
	 * OK, there are no updates running now, and all cached data is
	 * synced to disk.  We are now in a completely consistent state
	 * which doesn't have anything in the journal, and we know that
	 * no filesystem updates are running, so it is safe to modify
	 * the inode's in-core data-journaling state flag now.
	 */

	if (val)
		ext4_set_inode_flag(inode, EXT4_INODE_JOURNAL_DATA);
	else {
		err = jbd2_journal_flush(journal);
		if (err < 0) {
			jbd2_journal_unlock_updates(journal);
			percpu_up_write(&sbi->s_journal_flag_rwsem);
			return err;
		}
		ext4_clear_inode_flag(inode, EXT4_INODE_JOURNAL_DATA);
	}
	ext4_set_aops(inode);

	jbd2_journal_unlock_updates(journal);
	percpu_up_write(&sbi->s_journal_flag_rwsem);

	if (val)
		up_write(&EXT4_I(inode)->i_mmap_sem);

	/* Finally we can mark the inode as dirty. */

	handle = ext4_journal_start(inode, EXT4_HT_INODE, 1);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	err = ext4_mark_inode_dirty(handle, inode);
	ext4_handle_sync(handle);
	ext4_journal_stop(handle);
	ext4_std_error(inode->i_sb, err);

	return err;
}