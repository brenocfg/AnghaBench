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
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct reiserfs_transaction_handle {scalar_t__ t_trans_id; } ;
struct TYPE_2__ {scalar_t__ reserved_blocks; int /*<<< orphan*/  commit_wq; int /*<<< orphan*/  lock; int /*<<< orphan*/  s_mount_state; } ;

/* Variables and functions */
 TYPE_1__* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  SB_BUFFER_WITH_SB (struct super_block*) ; 
 int /*<<< orphan*/  SB_DISK_SUPER_BLOCK (struct super_block*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  journal_begin (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  journal_release (struct reiserfs_transaction_handle*,struct super_block*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_statistics (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_free_bitmap_cache (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reiserfs_quota_off_umount (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  reiserfs_write_lock (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (struct super_block*) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  set_sb_umount_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reiserfs_put_super(struct super_block *s)
{
	struct reiserfs_transaction_handle th;
	th.t_trans_id = 0;

	reiserfs_quota_off_umount(s);

	reiserfs_write_lock(s);

	/*
	 * change file system state to current state if it was mounted
	 * with read-write permissions
	 */
	if (!sb_rdonly(s)) {
		if (!journal_begin(&th, s, 10)) {
			reiserfs_prepare_for_journal(s, SB_BUFFER_WITH_SB(s),
						     1);
			set_sb_umount_state(SB_DISK_SUPER_BLOCK(s),
					    REISERFS_SB(s)->s_mount_state);
			journal_mark_dirty(&th, SB_BUFFER_WITH_SB(s));
		}
	}

	/*
	 * note, journal_release checks for readonly mount, and can
	 * decide not to do a journal_end
	 */
	journal_release(&th, s);

	reiserfs_free_bitmap_cache(s);

	brelse(SB_BUFFER_WITH_SB(s));

	print_statistics(s);

	if (REISERFS_SB(s)->reserved_blocks != 0) {
		reiserfs_warning(s, "green-2005", "reserved blocks left %d",
				 REISERFS_SB(s)->reserved_blocks);
	}

	reiserfs_write_unlock(s);
	mutex_destroy(&REISERFS_SB(s)->lock);
	destroy_workqueue(REISERFS_SB(s)->commit_wq);
	kfree(s->s_fs_info);
	s->s_fs_info = NULL;
}