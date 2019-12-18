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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int /*<<< orphan*/  sb; struct inode* osb_tl_inode; } ;
struct ocfs2_refcount_tree {int dummy; } ;
struct ocfs2_extent_tree {int /*<<< orphan*/  et_root_bh; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int OCFS2_EXT_REFCOUNTED ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int __ocfs2_flush_truncate_log (struct ocfs2_super*) ; 
 int /*<<< orphan*/  dquot_free_space_nodirty (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_blocks_to_clusters (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int ocfs2_decrease_refcount (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*,int) ; 
 int ocfs2_et_root_journal_access (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_et_update_clusters (struct ocfs2_extent_tree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_is_refcount_inode (struct inode*) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ocfs2_lock_refcount_tree (struct ocfs2_super*,scalar_t__,int,struct ocfs2_refcount_tree**,int /*<<< orphan*/ *) ; 
 int ocfs2_prepare_refcount_change_for_del (struct inode*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int*,int*) ; 
 int ocfs2_remove_extent (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*) ; 
 scalar_t__ ocfs2_remove_extent_credits (int /*<<< orphan*/ ) ; 
 int ocfs2_reserve_blocks_for_rec_trunc (struct inode*,struct ocfs2_extent_tree*,int,struct ocfs2_alloc_context**,int) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,scalar_t__) ; 
 int ocfs2_truncate_log_append (struct ocfs2_super*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_truncate_log_needs_flush (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_unlock_refcount_tree (struct ocfs2_super*,struct ocfs2_refcount_tree*,int) ; 
 int /*<<< orphan*/  ocfs2_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int) ; 

int ocfs2_remove_btree_range(struct inode *inode,
			     struct ocfs2_extent_tree *et,
			     u32 cpos, u32 phys_cpos, u32 len, int flags,
			     struct ocfs2_cached_dealloc_ctxt *dealloc,
			     u64 refcount_loc, bool refcount_tree_locked)
{
	int ret, credits = 0, extra_blocks = 0;
	u64 phys_blkno = ocfs2_clusters_to_blocks(inode->i_sb, phys_cpos);
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct inode *tl_inode = osb->osb_tl_inode;
	handle_t *handle;
	struct ocfs2_alloc_context *meta_ac = NULL;
	struct ocfs2_refcount_tree *ref_tree = NULL;

	if ((flags & OCFS2_EXT_REFCOUNTED) && len) {
		BUG_ON(!ocfs2_is_refcount_inode(inode));

		if (!refcount_tree_locked) {
			ret = ocfs2_lock_refcount_tree(osb, refcount_loc, 1,
						       &ref_tree, NULL);
			if (ret) {
				mlog_errno(ret);
				goto bail;
			}
		}

		ret = ocfs2_prepare_refcount_change_for_del(inode,
							    refcount_loc,
							    phys_blkno,
							    len,
							    &credits,
							    &extra_blocks);
		if (ret < 0) {
			mlog_errno(ret);
			goto bail;
		}
	}

	ret = ocfs2_reserve_blocks_for_rec_trunc(inode, et, 1, &meta_ac,
						 extra_blocks);
	if (ret) {
		mlog_errno(ret);
		goto bail;
	}

	inode_lock(tl_inode);

	if (ocfs2_truncate_log_needs_flush(osb)) {
		ret = __ocfs2_flush_truncate_log(osb);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}
	}

	handle = ocfs2_start_trans(osb,
			ocfs2_remove_extent_credits(osb->sb) + credits);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_et_root_journal_access(handle, et,
					   OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	dquot_free_space_nodirty(inode,
				  ocfs2_clusters_to_bytes(inode->i_sb, len));

	ret = ocfs2_remove_extent(handle, et, cpos, len, meta_ac, dealloc);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	ocfs2_et_update_clusters(et, -len);
	ocfs2_update_inode_fsync_trans(handle, inode, 1);

	ocfs2_journal_dirty(handle, et->et_root_bh);

	if (phys_blkno) {
		if (flags & OCFS2_EXT_REFCOUNTED)
			ret = ocfs2_decrease_refcount(inode, handle,
					ocfs2_blocks_to_clusters(osb->sb,
								 phys_blkno),
					len, meta_ac,
					dealloc, 1);
		else
			ret = ocfs2_truncate_log_append(osb, handle,
							phys_blkno, len);
		if (ret)
			mlog_errno(ret);

	}

out_commit:
	ocfs2_commit_trans(osb, handle);
out:
	inode_unlock(tl_inode);
bail:
	if (meta_ac)
		ocfs2_free_alloc_context(meta_ac);

	if (ref_tree)
		ocfs2_unlock_refcount_tree(osb, ref_tree, 1);

	return ret;
}