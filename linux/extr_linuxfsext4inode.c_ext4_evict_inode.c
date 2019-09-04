#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_5__ {scalar_t__ nrpages; } ;
struct inode {scalar_t__ i_ino; int /*<<< orphan*/  i_sb; scalar_t__ i_blocks; scalar_t__ i_size; TYPE_1__ i_data; int /*<<< orphan*/  i_mode; scalar_t__ i_nlink; } ;
struct ext4_xattr_inode_array {int dummy; } ;
typedef  int /*<<< orphan*/  journal_t ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ __u32 ;
struct TYPE_7__ {scalar_t__ i_dtime; int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_datasync_tid; } ;
struct TYPE_6__ {int /*<<< orphan*/ * s_journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_HT_TRUNCATE ; 
 TYPE_4__* EXT4_I (struct inode*) ; 
 scalar_t__ EXT4_JOURNAL_INO ; 
 scalar_t__ EXT4_MAXQUOTAS_DEL_BLOCKS (int /*<<< orphan*/ ) ; 
 TYPE_3__* EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_NOQUOTA (struct inode*) ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  ext4_begin_ordered_truncate (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_blocks_for_truncate (struct inode*) ; 
 int /*<<< orphan*/  ext4_clear_inode (struct inode*) ; 
 int /*<<< orphan*/  ext4_error (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  ext4_free_inode (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_handle_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_inode_is_fast_symlink (struct inode*) ; 
 int /*<<< orphan*/ * ext4_journal_start (struct inode*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ext4_journal_stop (int /*<<< orphan*/ *) ; 
 int ext4_mark_inode_dirty (int /*<<< orphan*/ *,struct inode*) ; 
 int /*<<< orphan*/  ext4_orphan_del (int /*<<< orphan*/ *,struct inode*) ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 scalar_t__ ext4_should_order_data (struct inode*) ; 
 int /*<<< orphan*/  ext4_std_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ext4_truncate (struct inode*) ; 
 int /*<<< orphan*/  ext4_warning (int /*<<< orphan*/ ,char*,int) ; 
 int ext4_xattr_delete_inode (int /*<<< orphan*/ *,struct inode*,struct ext4_xattr_inode_array**,int) ; 
 int /*<<< orphan*/  ext4_xattr_inode_array_free (struct ext4_xattr_inode_array*) ; 
 int /*<<< orphan*/  filemap_write_and_wait (TYPE_1__*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  jbd2_complete_transaction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_get_real_seconds () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sb_end_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_intwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ext4_evict_inode (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages_final (TYPE_1__*) ; 

void ext4_evict_inode(struct inode *inode)
{
	handle_t *handle;
	int err;
	int extra_credits = 3;
	struct ext4_xattr_inode_array *ea_inode_array = NULL;

	trace_ext4_evict_inode(inode);

	if (inode->i_nlink) {
		/*
		 * When journalling data dirty buffers are tracked only in the
		 * journal. So although mm thinks everything is clean and
		 * ready for reaping the inode might still have some pages to
		 * write in the running transaction or waiting to be
		 * checkpointed. Thus calling jbd2_journal_invalidatepage()
		 * (via truncate_inode_pages()) to discard these buffers can
		 * cause data loss. Also even if we did not discard these
		 * buffers, we would have no way to find them after the inode
		 * is reaped and thus user could see stale data if he tries to
		 * read them before the transaction is checkpointed. So be
		 * careful and force everything to disk here... We use
		 * ei->i_datasync_tid to store the newest transaction
		 * containing inode's data.
		 *
		 * Note that directories do not have this problem because they
		 * don't use page cache.
		 */
		if (inode->i_ino != EXT4_JOURNAL_INO &&
		    ext4_should_journal_data(inode) &&
		    (S_ISLNK(inode->i_mode) || S_ISREG(inode->i_mode)) &&
		    inode->i_data.nrpages) {
			journal_t *journal = EXT4_SB(inode->i_sb)->s_journal;
			tid_t commit_tid = EXT4_I(inode)->i_datasync_tid;

			jbd2_complete_transaction(journal, commit_tid);
			filemap_write_and_wait(&inode->i_data);
		}
		truncate_inode_pages_final(&inode->i_data);

		goto no_delete;
	}

	if (is_bad_inode(inode))
		goto no_delete;
	dquot_initialize(inode);

	if (ext4_should_order_data(inode))
		ext4_begin_ordered_truncate(inode, 0);
	truncate_inode_pages_final(&inode->i_data);

	/*
	 * Protect us against freezing - iput() caller didn't have to have any
	 * protection against it
	 */
	sb_start_intwrite(inode->i_sb);

	if (!IS_NOQUOTA(inode))
		extra_credits += EXT4_MAXQUOTAS_DEL_BLOCKS(inode->i_sb);

	handle = ext4_journal_start(inode, EXT4_HT_TRUNCATE,
				 ext4_blocks_for_truncate(inode)+extra_credits);
	if (IS_ERR(handle)) {
		ext4_std_error(inode->i_sb, PTR_ERR(handle));
		/*
		 * If we're going to skip the normal cleanup, we still need to
		 * make sure that the in-core orphan linked list is properly
		 * cleaned up.
		 */
		ext4_orphan_del(NULL, inode);
		sb_end_intwrite(inode->i_sb);
		goto no_delete;
	}

	if (IS_SYNC(inode))
		ext4_handle_sync(handle);

	/*
	 * Set inode->i_size to 0 before calling ext4_truncate(). We need
	 * special handling of symlinks here because i_size is used to
	 * determine whether ext4_inode_info->i_data contains symlink data or
	 * block mappings. Setting i_size to 0 will remove its fast symlink
	 * status. Erase i_data so that it becomes a valid empty block map.
	 */
	if (ext4_inode_is_fast_symlink(inode))
		memset(EXT4_I(inode)->i_data, 0, sizeof(EXT4_I(inode)->i_data));
	inode->i_size = 0;
	err = ext4_mark_inode_dirty(handle, inode);
	if (err) {
		ext4_warning(inode->i_sb,
			     "couldn't mark inode dirty (err %d)", err);
		goto stop_handle;
	}
	if (inode->i_blocks) {
		err = ext4_truncate(inode);
		if (err) {
			ext4_error(inode->i_sb,
				   "couldn't truncate inode %lu (err %d)",
				   inode->i_ino, err);
			goto stop_handle;
		}
	}

	/* Remove xattr references. */
	err = ext4_xattr_delete_inode(handle, inode, &ea_inode_array,
				      extra_credits);
	if (err) {
		ext4_warning(inode->i_sb, "xattr delete (err %d)", err);
stop_handle:
		ext4_journal_stop(handle);
		ext4_orphan_del(NULL, inode);
		sb_end_intwrite(inode->i_sb);
		ext4_xattr_inode_array_free(ea_inode_array);
		goto no_delete;
	}

	/*
	 * Kill off the orphan record which ext4_truncate created.
	 * AKPM: I think this can be inside the above `if'.
	 * Note that ext4_orphan_del() has to be able to cope with the
	 * deletion of a non-existent orphan - this is because we don't
	 * know if ext4_truncate() actually created an orphan record.
	 * (Well, we could do this if we need to, but heck - it works)
	 */
	ext4_orphan_del(handle, inode);
	EXT4_I(inode)->i_dtime	= (__u32)ktime_get_real_seconds();

	/*
	 * One subtle ordering requirement: if anything has gone wrong
	 * (transaction abort, IO errors, whatever), then we can still
	 * do these next steps (the fs will already have been marked as
	 * having errors), but we can't free the inode if the mark_dirty
	 * fails.
	 */
	if (ext4_mark_inode_dirty(handle, inode))
		/* If that failed, just do the required in-core inode clear. */
		ext4_clear_inode(inode);
	else
		ext4_free_inode(handle, inode);
	ext4_journal_stop(handle);
	sb_end_intwrite(inode->i_sb);
	ext4_xattr_inode_array_free(ea_inode_array);
	return;
no_delete:
	ext4_clear_inode(inode);	/* We must guarantee clearing of inode... */
}