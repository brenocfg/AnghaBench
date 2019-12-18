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
struct super_block {int dummy; } ;
struct reiserfs_transaction_handle {int /*<<< orphan*/  t_trans_id; } ;
struct reiserfs_journal {int /*<<< orphan*/  j_work; } ;
typedef  int /*<<< orphan*/  myth ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  FLUSH_ALL ; 
 int /*<<< orphan*/  SB_BUFFER_WITH_SB (struct super_block*) ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_journal_end (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_journal_ram (struct super_block*) ; 
 int /*<<< orphan*/  journal_join (struct reiserfs_transaction_handle*,struct super_block*) ; 
 int /*<<< orphan*/  journal_join_abort (struct reiserfs_transaction_handle*,struct super_block*) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reiserfs_cancel_old_flush (struct super_block*) ; 
 scalar_t__ reiserfs_is_journal_aborted (struct reiserfs_journal*) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reiserfs_write_lock (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (struct super_block*) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 

__attribute__((used)) static int do_journal_release(struct reiserfs_transaction_handle *th,
			      struct super_block *sb, int error)
{
	struct reiserfs_transaction_handle myth;
	struct reiserfs_journal *journal = SB_JOURNAL(sb);

	/*
	 * we only want to flush out transactions if we were
	 * called with error == 0
	 */
	if (!error && !sb_rdonly(sb)) {
		/* end the current trans */
		BUG_ON(!th->t_trans_id);
		do_journal_end(th, FLUSH_ALL);

		/*
		 * make sure something gets logged to force
		 * our way into the flush code
		 */
		if (!journal_join(&myth, sb)) {
			reiserfs_prepare_for_journal(sb,
						     SB_BUFFER_WITH_SB(sb),
						     1);
			journal_mark_dirty(&myth, SB_BUFFER_WITH_SB(sb));
			do_journal_end(&myth, FLUSH_ALL);
		}
	}

	/* this also catches errors during the do_journal_end above */
	if (!error && reiserfs_is_journal_aborted(journal)) {
		memset(&myth, 0, sizeof(myth));
		if (!journal_join_abort(&myth, sb)) {
			reiserfs_prepare_for_journal(sb,
						     SB_BUFFER_WITH_SB(sb),
						     1);
			journal_mark_dirty(&myth, SB_BUFFER_WITH_SB(sb));
			do_journal_end(&myth, FLUSH_ALL);
		}
	}


	/*
	 * We must release the write lock here because
	 * the workqueue job (flush_async_commit) needs this lock
	 */
	reiserfs_write_unlock(sb);

	/*
	 * Cancel flushing of old commits. Note that neither of these works
	 * will be requeued because superblock is being shutdown and doesn't
	 * have SB_ACTIVE set.
	 */
	reiserfs_cancel_old_flush(sb);
	/* wait for all commits to finish */
	cancel_delayed_work_sync(&SB_JOURNAL(sb)->j_work);

	free_journal_ram(sb);

	reiserfs_write_lock(sb);

	return 0;
}