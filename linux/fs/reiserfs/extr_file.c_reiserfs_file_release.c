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
struct reiserfs_transaction_handle {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int i_flags; scalar_t__ i_prealloc_count; int /*<<< orphan*/  tailpack; int /*<<< orphan*/  openers; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* REISERFS_I (struct inode*) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int i_pack_on_close_mask ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int journal_begin (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ,int) ; 
 int journal_end (struct reiserfs_transaction_handle*) ; 
 int journal_join_abort (struct reiserfs_transaction_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_discard_prealloc (struct reiserfs_transaction_handle*,struct inode*) ; 
 int reiserfs_truncate_file (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ tail_has_to_be_packed (struct inode*) ; 

__attribute__((used)) static int reiserfs_file_release(struct inode *inode, struct file *filp)
{

	struct reiserfs_transaction_handle th;
	int err;
	int jbegin_failure = 0;

	BUG_ON(!S_ISREG(inode->i_mode));

        if (atomic_add_unless(&REISERFS_I(inode)->openers, -1, 1))
		return 0;

	mutex_lock(&REISERFS_I(inode)->tailpack);

        if (!atomic_dec_and_test(&REISERFS_I(inode)->openers)) {
		mutex_unlock(&REISERFS_I(inode)->tailpack);
		return 0;
	}

	/* fast out for when nothing needs to be done */
	if ((!(REISERFS_I(inode)->i_flags & i_pack_on_close_mask) ||
	     !tail_has_to_be_packed(inode)) &&
	    REISERFS_I(inode)->i_prealloc_count <= 0) {
		mutex_unlock(&REISERFS_I(inode)->tailpack);
		return 0;
	}

	reiserfs_write_lock(inode->i_sb);
	/*
	 * freeing preallocation only involves relogging blocks that
	 * are already in the current transaction.  preallocation gets
	 * freed at the end of each transaction, so it is impossible for
	 * us to log any additional blocks (including quota blocks)
	 */
	err = journal_begin(&th, inode->i_sb, 1);
	if (err) {
		/*
		 * uh oh, we can't allow the inode to go away while there
		 * is still preallocation blocks pending.  Try to join the
		 * aborted transaction
		 */
		jbegin_failure = err;
		err = journal_join_abort(&th, inode->i_sb);

		if (err) {
			/*
			 * hmpf, our choices here aren't good.  We can pin
			 * the inode which will disallow unmount from ever
			 * happening, we can do nothing, which will corrupt
			 * random memory on unmount, or we can forcibly
			 * remove the file from the preallocation list, which
			 * will leak blocks on disk.  Lets pin the inode
			 * and let the admin know what is going on.
			 */
			igrab(inode);
			reiserfs_warning(inode->i_sb, "clm-9001",
					 "pinning inode %lu because the "
					 "preallocation can't be freed",
					 inode->i_ino);
			goto out;
		}
	}
	reiserfs_update_inode_transaction(inode);

#ifdef REISERFS_PREALLOCATE
	reiserfs_discard_prealloc(&th, inode);
#endif
	err = journal_end(&th);

	/* copy back the error code from journal_begin */
	if (!err)
		err = jbegin_failure;

	if (!err &&
	    (REISERFS_I(inode)->i_flags & i_pack_on_close_mask) &&
	    tail_has_to_be_packed(inode)) {

		/*
		 * if regular file is released by last holder and it has been
		 * appended (we append by unformatted node only) or its direct
		 * item(s) had to be converted, then it may have to be
		 * indirect2direct converted
		 */
		err = reiserfs_truncate_file(inode, 0);
	}
out:
	reiserfs_write_unlock(inode->i_sb);
	mutex_unlock(&REISERFS_I(inode)->tailpack);
	return err;
}