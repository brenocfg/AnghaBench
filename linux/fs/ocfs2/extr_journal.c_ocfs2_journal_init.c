#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {int /*<<< orphan*/  slot_num; } ;
struct ocfs2_journal {int /*<<< orphan*/  j_state; struct buffer_head* j_bh; struct inode* j_inode; TYPE_3__* j_journal; struct ocfs2_super* j_osb; } ;
struct TYPE_6__ {int /*<<< orphan*/  ij_flags; } ;
struct TYPE_7__ {TYPE_1__ journal1; } ;
struct ocfs2_dinode {TYPE_2__ id1; } ;
struct inode {scalar_t__ i_blocks; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  j_maxlen; } ;
typedef  TYPE_3__ journal_t ;
struct TYPE_9__ {int /*<<< orphan*/  ip_open_count; int /*<<< orphan*/  ip_clusters; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EACCES ; 
 int EINVAL ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  JOURNAL_SYSTEM_INODE ; 
 int /*<<< orphan*/  ML_ERROR ; 
 TYPE_5__* OCFS2_I (struct inode*) ; 
 int OCFS2_JOURNAL_DIRTY_FL ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_LOADED ; 
 int /*<<< orphan*/  OCFS2_META_LOCK_RECOVERY ; 
 scalar_t__ OCFS2_MIN_JOURNAL_SIZE ; 
 int /*<<< orphan*/  SET_INODE_JOURNAL (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 TYPE_3__* jbd2_journal_init_inode (struct inode*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 struct inode* ocfs2_get_system_file_inode (struct ocfs2_super*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ocfs2_inode_lock_full (struct inode*,struct buffer_head**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int) ; 
 int /*<<< orphan*/  ocfs2_set_journal_params (struct ocfs2_super*) ; 
 int /*<<< orphan*/  trace_ocfs2_journal_init (scalar_t__,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_journal_init_maxlen (int /*<<< orphan*/ ) ; 

int ocfs2_journal_init(struct ocfs2_journal *journal, int *dirty)
{
	int status = -1;
	struct inode *inode = NULL; /* the journal inode */
	journal_t *j_journal = NULL;
	struct ocfs2_dinode *di = NULL;
	struct buffer_head *bh = NULL;
	struct ocfs2_super *osb;
	int inode_lock = 0;

	BUG_ON(!journal);

	osb = journal->j_osb;

	/* already have the inode for our journal */
	inode = ocfs2_get_system_file_inode(osb, JOURNAL_SYSTEM_INODE,
					    osb->slot_num);
	if (inode == NULL) {
		status = -EACCES;
		mlog_errno(status);
		goto done;
	}
	if (is_bad_inode(inode)) {
		mlog(ML_ERROR, "access error (bad inode)\n");
		iput(inode);
		inode = NULL;
		status = -EACCES;
		goto done;
	}

	SET_INODE_JOURNAL(inode);
	OCFS2_I(inode)->ip_open_count++;

	/* Skip recovery waits here - journal inode metadata never
	 * changes in a live cluster so it can be considered an
	 * exception to the rule. */
	status = ocfs2_inode_lock_full(inode, &bh, 1, OCFS2_META_LOCK_RECOVERY);
	if (status < 0) {
		if (status != -ERESTARTSYS)
			mlog(ML_ERROR, "Could not get lock on journal!\n");
		goto done;
	}

	inode_lock = 1;
	di = (struct ocfs2_dinode *)bh->b_data;

	if (i_size_read(inode) <  OCFS2_MIN_JOURNAL_SIZE) {
		mlog(ML_ERROR, "Journal file size (%lld) is too small!\n",
		     i_size_read(inode));
		status = -EINVAL;
		goto done;
	}

	trace_ocfs2_journal_init(i_size_read(inode),
				 (unsigned long long)inode->i_blocks,
				 OCFS2_I(inode)->ip_clusters);

	/* call the kernels journal init function now */
	j_journal = jbd2_journal_init_inode(inode);
	if (j_journal == NULL) {
		mlog(ML_ERROR, "Linux journal layer error\n");
		status = -EINVAL;
		goto done;
	}

	trace_ocfs2_journal_init_maxlen(j_journal->j_maxlen);

	*dirty = (le32_to_cpu(di->id1.journal1.ij_flags) &
		  OCFS2_JOURNAL_DIRTY_FL);

	journal->j_journal = j_journal;
	journal->j_inode = inode;
	journal->j_bh = bh;

	ocfs2_set_journal_params(osb);

	journal->j_state = OCFS2_JOURNAL_LOADED;

	status = 0;
done:
	if (status < 0) {
		if (inode_lock)
			ocfs2_inode_unlock(inode, 1);
		brelse(bh);
		if (inode) {
			OCFS2_I(inode)->ip_open_count--;
			iput(inode);
		}
	}

	return status;
}