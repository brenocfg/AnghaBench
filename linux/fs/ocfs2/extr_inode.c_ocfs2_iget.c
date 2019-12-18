#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_6__ {void* t_tid; } ;
typedef  TYPE_2__ transaction_t ;
typedef  void* tid_t ;
struct super_block {int dummy; } ;
struct ocfs2_super {struct super_block* sb; } ;
struct ocfs2_inode_info {scalar_t__ ip_blkno; void* i_datasync_tid; void* i_sync_tid; } ;
struct ocfs2_find_inode_args {unsigned int fi_flags; int fi_sysfile_type; int /*<<< orphan*/  fi_ino; scalar_t__ fi_blkno; } ;
struct inode {int i_state; } ;
struct TYPE_7__ {int /*<<< orphan*/  j_state_lock; void* j_commit_sequence; TYPE_2__* j_committing_transaction; TYPE_2__* j_running_transaction; } ;
typedef  TYPE_3__ journal_t ;
struct TYPE_8__ {TYPE_1__* journal; } ;
struct TYPE_5__ {TYPE_3__* j_journal; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int ESTALE ; 
 int /*<<< orphan*/  IS_ERR (struct inode*) ; 
 int I_NEW ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 TYPE_4__* OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  PTR_ERR (struct inode*) ; 
 struct inode* iget5_locked (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_find_inode_args*) ; 
 int /*<<< orphan*/  ino_from_blkno (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_find_actor ; 
 int /*<<< orphan*/  ocfs2_init_locked_inode ; 
 int ocfs2_read_locked_inode (struct inode*,struct ocfs2_find_inode_args*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_iget5_locked (int) ; 
 int /*<<< orphan*/  trace_ocfs2_iget_begin (unsigned long long,unsigned int,int) ; 
 int /*<<< orphan*/  trace_ocfs2_iget_end (struct inode*,unsigned long long) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *ocfs2_iget(struct ocfs2_super *osb, u64 blkno, unsigned flags,
			 int sysfile_type)
{
	int rc = -ESTALE;
	struct inode *inode = NULL;
	struct super_block *sb = osb->sb;
	struct ocfs2_find_inode_args args;
	journal_t *journal = OCFS2_SB(sb)->journal->j_journal;

	trace_ocfs2_iget_begin((unsigned long long)blkno, flags,
			       sysfile_type);

	/* Ok. By now we've either got the offsets passed to us by the
	 * caller, or we just pulled them off the bh. Lets do some
	 * sanity checks to make sure they're OK. */
	if (blkno == 0) {
		inode = ERR_PTR(-EINVAL);
		mlog_errno(PTR_ERR(inode));
		goto bail;
	}

	args.fi_blkno = blkno;
	args.fi_flags = flags;
	args.fi_ino = ino_from_blkno(sb, blkno);
	args.fi_sysfile_type = sysfile_type;

	inode = iget5_locked(sb, args.fi_ino, ocfs2_find_actor,
			     ocfs2_init_locked_inode, &args);
	/* inode was *not* in the inode cache. 2.6.x requires
	 * us to do our own read_inode call and unlock it
	 * afterwards. */
	if (inode == NULL) {
		inode = ERR_PTR(-ENOMEM);
		mlog_errno(PTR_ERR(inode));
		goto bail;
	}
	trace_ocfs2_iget5_locked(inode->i_state);
	if (inode->i_state & I_NEW) {
		rc = ocfs2_read_locked_inode(inode, &args);
		unlock_new_inode(inode);
	}
	if (is_bad_inode(inode)) {
		iput(inode);
		inode = ERR_PTR(rc);
		goto bail;
	}

	/*
	 * Set transaction id's of transactions that have to be committed
	 * to finish f[data]sync. We set them to currently running transaction
	 * as we cannot be sure that the inode or some of its metadata isn't
	 * part of the transaction - the inode could have been reclaimed and
	 * now it is reread from disk.
	 */
	if (journal) {
		transaction_t *transaction;
		tid_t tid;
		struct ocfs2_inode_info *oi = OCFS2_I(inode);

		read_lock(&journal->j_state_lock);
		if (journal->j_running_transaction)
			transaction = journal->j_running_transaction;
		else
			transaction = journal->j_committing_transaction;
		if (transaction)
			tid = transaction->t_tid;
		else
			tid = journal->j_commit_sequence;
		read_unlock(&journal->j_state_lock);
		oi->i_sync_tid = tid;
		oi->i_datasync_tid = tid;
	}

bail:
	if (!IS_ERR(inode)) {
		trace_ocfs2_iget_end(inode, 
			(unsigned long long)OCFS2_I(inode)->ip_blkno);
	}

	return inode;
}