#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_list; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_clusters; TYPE_1__ id2; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  enum ocfs2_alloc_restarted { ____Placeholder_ocfs2_alloc_restarted } ocfs2_alloc_restarted ;
struct TYPE_4__ {scalar_t__ ip_clusters; scalar_t__ ip_blkno; int /*<<< orphan*/  ip_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int RESTART_META ; 
 int RESTART_NONE ; 
 int RESTART_TRANS ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int dquot_alloc_space_nodirty (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dquot_free_space (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_add_inode_data (struct ocfs2_super*,struct inode*,scalar_t__*,scalar_t__,int,struct buffer_head*,int /*<<< orphan*/ *,struct ocfs2_alloc_context*,struct ocfs2_alloc_context*,int*) ; 
 int ocfs2_allocate_extend_trans (int /*<<< orphan*/ *,int) ; 
 int ocfs2_calc_extend_credits (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_bytes (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_init_dinode_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_lock_allocators (struct inode*,struct ocfs2_extent_tree*,scalar_t__,int /*<<< orphan*/ ,struct ocfs2_alloc_context**,struct ocfs2_alloc_context**) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_sparse_alloc (struct ocfs2_super*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_extend_allocation (unsigned long long,unsigned long long,scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  trace_ocfs2_extend_allocation_end (scalar_t__,scalar_t__,unsigned long long,scalar_t__,unsigned long long) ; 

__attribute__((used)) static int ocfs2_extend_allocation(struct inode *inode, u32 logical_start,
				   u32 clusters_to_add, int mark_unwritten)
{
	int status = 0;
	int restart_func = 0;
	int credits;
	u32 prev_clusters;
	struct buffer_head *bh = NULL;
	struct ocfs2_dinode *fe = NULL;
	handle_t *handle = NULL;
	struct ocfs2_alloc_context *data_ac = NULL;
	struct ocfs2_alloc_context *meta_ac = NULL;
	enum ocfs2_alloc_restarted why = RESTART_NONE;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_extent_tree et;
	int did_quota = 0;

	/*
	 * Unwritten extent only exists for file systems which
	 * support holes.
	 */
	BUG_ON(mark_unwritten && !ocfs2_sparse_alloc(osb));

	status = ocfs2_read_inode_block(inode, &bh);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}
	fe = (struct ocfs2_dinode *) bh->b_data;

restart_all:
	BUG_ON(le32_to_cpu(fe->i_clusters) != OCFS2_I(inode)->ip_clusters);

	ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(inode), bh);
	status = ocfs2_lock_allocators(inode, &et, clusters_to_add, 0,
				       &data_ac, &meta_ac);
	if (status) {
		mlog_errno(status);
		goto leave;
	}

	credits = ocfs2_calc_extend_credits(osb->sb, &fe->id2.i_list);
	handle = ocfs2_start_trans(osb, credits);
	if (IS_ERR(handle)) {
		status = PTR_ERR(handle);
		handle = NULL;
		mlog_errno(status);
		goto leave;
	}

restarted_transaction:
	trace_ocfs2_extend_allocation(
		(unsigned long long)OCFS2_I(inode)->ip_blkno,
		(unsigned long long)i_size_read(inode),
		le32_to_cpu(fe->i_clusters), clusters_to_add,
		why, restart_func);

	status = dquot_alloc_space_nodirty(inode,
			ocfs2_clusters_to_bytes(osb->sb, clusters_to_add));
	if (status)
		goto leave;
	did_quota = 1;

	/* reserve a write to the file entry early on - that we if we
	 * run out of credits in the allocation path, we can still
	 * update i_size. */
	status = ocfs2_journal_access_di(handle, INODE_CACHE(inode), bh,
					 OCFS2_JOURNAL_ACCESS_WRITE);
	if (status < 0) {
		mlog_errno(status);
		goto leave;
	}

	prev_clusters = OCFS2_I(inode)->ip_clusters;

	status = ocfs2_add_inode_data(osb,
				      inode,
				      &logical_start,
				      clusters_to_add,
				      mark_unwritten,
				      bh,
				      handle,
				      data_ac,
				      meta_ac,
				      &why);
	if ((status < 0) && (status != -EAGAIN)) {
		if (status != -ENOSPC)
			mlog_errno(status);
		goto leave;
	}
	ocfs2_update_inode_fsync_trans(handle, inode, 1);
	ocfs2_journal_dirty(handle, bh);

	spin_lock(&OCFS2_I(inode)->ip_lock);
	clusters_to_add -= (OCFS2_I(inode)->ip_clusters - prev_clusters);
	spin_unlock(&OCFS2_I(inode)->ip_lock);
	/* Release unused quota reservation */
	dquot_free_space(inode,
			ocfs2_clusters_to_bytes(osb->sb, clusters_to_add));
	did_quota = 0;

	if (why != RESTART_NONE && clusters_to_add) {
		if (why == RESTART_META) {
			restart_func = 1;
			status = 0;
		} else {
			BUG_ON(why != RESTART_TRANS);

			status = ocfs2_allocate_extend_trans(handle, 1);
			if (status < 0) {
				/* handle still has to be committed at
				 * this point. */
				status = -ENOMEM;
				mlog_errno(status);
				goto leave;
			}
			goto restarted_transaction;
		}
	}

	trace_ocfs2_extend_allocation_end(OCFS2_I(inode)->ip_blkno,
	     le32_to_cpu(fe->i_clusters),
	     (unsigned long long)le64_to_cpu(fe->i_size),
	     OCFS2_I(inode)->ip_clusters,
	     (unsigned long long)i_size_read(inode));

leave:
	if (status < 0 && did_quota)
		dquot_free_space(inode,
			ocfs2_clusters_to_bytes(osb->sb, clusters_to_add));
	if (handle) {
		ocfs2_commit_trans(osb, handle);
		handle = NULL;
	}
	if (data_ac) {
		ocfs2_free_alloc_context(data_ac);
		data_ac = NULL;
	}
	if (meta_ac) {
		ocfs2_free_alloc_context(meta_ac);
		meta_ac = NULL;
	}
	if ((!status) && restart_func) {
		restart_func = 0;
		goto restart_all;
	}
	brelse(bh);
	bh = NULL;

	return status;
}