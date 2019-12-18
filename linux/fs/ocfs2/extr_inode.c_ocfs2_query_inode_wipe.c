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
struct ocfs2_inode_info {int ip_flags; scalar_t__ ip_blkno; } ;
struct ocfs2_dinode {int i_flags; int i_dyn_features; int /*<<< orphan*/  i_orphaned_slot; scalar_t__ i_dtime; int /*<<< orphan*/  i_blkno; } ;
struct inode {int /*<<< orphan*/  i_nlink; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EEXIST ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS2_HAS_REFCOUNT_FL ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INODE_SKIP_ORPHAN_DIR ; 
 int /*<<< orphan*/  OCFS2_ORPHANED_FL ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long,unsigned long long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_inode_is_valid_to_delete (struct inode*) ; 
 int ocfs2_try_open_lock (struct inode*,int) ; 
 int /*<<< orphan*/  trace_ocfs2_query_inode_wipe_begin (unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_query_inode_wipe_end (int,int) ; 
 int /*<<< orphan*/  trace_ocfs2_query_inode_wipe_succ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_query_inode_wipe(struct inode *inode,
				  struct buffer_head *di_bh,
				  int *wipe)
{
	int status = 0, reason = 0;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_dinode *di;

	*wipe = 0;

	trace_ocfs2_query_inode_wipe_begin((unsigned long long)oi->ip_blkno,
					   inode->i_nlink);

	/* While we were waiting for the cluster lock in
	 * ocfs2_delete_inode, another node might have asked to delete
	 * the inode. Recheck our flags to catch this. */
	if (!ocfs2_inode_is_valid_to_delete(inode)) {
		reason = 1;
		goto bail;
	}

	/* Now that we have an up to date inode, we can double check
	 * the link count. */
	if (inode->i_nlink)
		goto bail;

	/* Do some basic inode verification... */
	di = (struct ocfs2_dinode *) di_bh->b_data;
	if (!(di->i_flags & cpu_to_le32(OCFS2_ORPHANED_FL)) &&
	    !(oi->ip_flags & OCFS2_INODE_SKIP_ORPHAN_DIR)) {
		/*
		 * Inodes in the orphan dir must have ORPHANED_FL.  The only
		 * inodes that come back out of the orphan dir are reflink
		 * targets. A reflink target may be moved out of the orphan
		 * dir between the time we scan the directory and the time we
		 * process it. This would lead to HAS_REFCOUNT_FL being set but
		 * ORPHANED_FL not.
		 */
		if (di->i_dyn_features & cpu_to_le16(OCFS2_HAS_REFCOUNT_FL)) {
			reason = 2;
			goto bail;
		}

		/* for lack of a better error? */
		status = -EEXIST;
		mlog(ML_ERROR,
		     "Inode %llu (on-disk %llu) not orphaned! "
		     "Disk flags  0x%x, inode flags 0x%x\n",
		     (unsigned long long)oi->ip_blkno,
		     (unsigned long long)le64_to_cpu(di->i_blkno),
		     le32_to_cpu(di->i_flags), oi->ip_flags);
		goto bail;
	}

	/* has someone already deleted us?! baaad... */
	if (di->i_dtime) {
		status = -EEXIST;
		mlog_errno(status);
		goto bail;
	}

	/*
	 * This is how ocfs2 determines whether an inode is still live
	 * within the cluster. Every node takes a shared read lock on
	 * the inode open lock in ocfs2_read_locked_inode(). When we
	 * get to ->delete_inode(), each node tries to convert it's
	 * lock to an exclusive. Trylocks are serialized by the inode
	 * meta data lock. If the upconvert succeeds, we know the inode
	 * is no longer live and can be deleted.
	 *
	 * Though we call this with the meta data lock held, the
	 * trylock keeps us from ABBA deadlock.
	 */
	status = ocfs2_try_open_lock(inode, 1);
	if (status == -EAGAIN) {
		status = 0;
		reason = 3;
		goto bail;
	}
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	*wipe = 1;
	trace_ocfs2_query_inode_wipe_succ(le16_to_cpu(di->i_orphaned_slot));

bail:
	trace_ocfs2_query_inode_wipe_end(status, reason);
	return status;
}