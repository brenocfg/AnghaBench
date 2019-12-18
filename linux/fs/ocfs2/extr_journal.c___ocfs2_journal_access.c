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
struct ocfs2_triggers {int /*<<< orphan*/  ot_triggers; } ;
struct ocfs2_super {int /*<<< orphan*/  journal; int /*<<< orphan*/  sb; } ;
struct ocfs2_caching_info {int /*<<< orphan*/  ci_ops; } ;
struct buffer_head {int b_state; scalar_t__ b_blocknr; int /*<<< orphan*/  b_size; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
#define  OCFS2_JOURNAL_ACCESS_CREATE 130 
#define  OCFS2_JOURNAL_ACCESS_UNDO 129 
#define  OCFS2_JOURNAL_ACCESS_WRITE 128 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ buffer_write_io_error (struct buffer_head*) ; 
 int jbd2_journal_get_undo_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int jbd2_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  jbd2_journal_set_triggers (struct buffer_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int ocfs2_error (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ocfs2_meta_ecc (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_get_super (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_io_lock (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_io_unlock (struct ocfs2_caching_info*) ; 
 scalar_t__ ocfs2_metadata_cache_owner (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_set_ci_lock_trans (int /*<<< orphan*/ ,struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  trace_ocfs2_journal_access (unsigned long long,unsigned long long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int __ocfs2_journal_access(handle_t *handle,
				  struct ocfs2_caching_info *ci,
				  struct buffer_head *bh,
				  struct ocfs2_triggers *triggers,
				  int type)
{
	int status;
	struct ocfs2_super *osb =
		OCFS2_SB(ocfs2_metadata_cache_get_super(ci));

	BUG_ON(!ci || !ci->ci_ops);
	BUG_ON(!handle);
	BUG_ON(!bh);

	trace_ocfs2_journal_access(
		(unsigned long long)ocfs2_metadata_cache_owner(ci),
		(unsigned long long)bh->b_blocknr, type, bh->b_size);

	/* we can safely remove this assertion after testing. */
	if (!buffer_uptodate(bh)) {
		mlog(ML_ERROR, "giving me a buffer that's not uptodate!\n");
		mlog(ML_ERROR, "b_blocknr=%llu, b_state=0x%lx\n",
		     (unsigned long long)bh->b_blocknr, bh->b_state);

		lock_buffer(bh);
		/*
		 * A previous transaction with a couple of buffer heads fail
		 * to checkpoint, so all the bhs are marked as BH_Write_EIO.
		 * For current transaction, the bh is just among those error
		 * bhs which previous transaction handle. We can't just clear
		 * its BH_Write_EIO and reuse directly, since other bhs are
		 * not written to disk yet and that will cause metadata
		 * inconsistency. So we should set fs read-only to avoid
		 * further damage.
		 */
		if (buffer_write_io_error(bh) && !buffer_uptodate(bh)) {
			unlock_buffer(bh);
			return ocfs2_error(osb->sb, "A previous attempt to "
					"write this buffer head failed\n");
		}
		unlock_buffer(bh);
	}

	/* Set the current transaction information on the ci so
	 * that the locking code knows whether it can drop it's locks
	 * on this ci or not. We're protected from the commit
	 * thread updating the current transaction id until
	 * ocfs2_commit_trans() because ocfs2_start_trans() took
	 * j_trans_barrier for us. */
	ocfs2_set_ci_lock_trans(osb->journal, ci);

	ocfs2_metadata_cache_io_lock(ci);
	switch (type) {
	case OCFS2_JOURNAL_ACCESS_CREATE:
	case OCFS2_JOURNAL_ACCESS_WRITE:
		status = jbd2_journal_get_write_access(handle, bh);
		break;

	case OCFS2_JOURNAL_ACCESS_UNDO:
		status = jbd2_journal_get_undo_access(handle, bh);
		break;

	default:
		status = -EINVAL;
		mlog(ML_ERROR, "Unknown access type!\n");
	}
	if (!status && ocfs2_meta_ecc(osb) && triggers)
		jbd2_journal_set_triggers(bh, &triggers->ot_triggers);
	ocfs2_metadata_cache_io_unlock(ci);

	if (status < 0)
		mlog(ML_ERROR, "Error %d getting %d access to buffer!\n",
		     status, type);

	return status;
}