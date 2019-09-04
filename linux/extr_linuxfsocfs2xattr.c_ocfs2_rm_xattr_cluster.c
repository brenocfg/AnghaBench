#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  xt_clusters; } ;
struct TYPE_5__ {TYPE_1__ xb_root; } ;
struct ocfs2_xattr_block {TYPE_2__ xb_attrs; } ;
struct ocfs2_super {int /*<<< orphan*/  sb; struct inode* osb_tl_inode; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_6__ {scalar_t__ ip_blkno; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 TYPE_3__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int __ocfs2_flush_truncate_log (struct ocfs2_super*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_delete_xattr_in_bucket ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int /*<<< orphan*/  ocfs2_init_dealloc_ctxt (struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_init_xattr_tree_extent_tree (struct ocfs2_extent_tree*,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int ocfs2_iterate_xattr_buckets (struct inode*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int ocfs2_journal_access_xb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int ocfs2_lock_allocators (struct inode*,struct ocfs2_extent_tree*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct ocfs2_alloc_context**) ; 
 int ocfs2_remove_extent (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_remove_extent_credits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_remove_xattr_clusters_from_cache (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_run_deallocs (struct ocfs2_super*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_schedule_truncate_log_flush (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_truncate_log_append (struct ocfs2_super*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ocfs2_truncate_log_needs_flush (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_update_inode_fsync_trans (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_rm_xattr_cluster (unsigned long long,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_rm_xattr_cluster(struct inode *inode,
				  struct buffer_head *root_bh,
				  u64 blkno,
				  u32 cpos,
				  u32 len,
				  void *para)
{
	int ret;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct inode *tl_inode = osb->osb_tl_inode;
	handle_t *handle;
	struct ocfs2_xattr_block *xb =
			(struct ocfs2_xattr_block *)root_bh->b_data;
	struct ocfs2_alloc_context *meta_ac = NULL;
	struct ocfs2_cached_dealloc_ctxt dealloc;
	struct ocfs2_extent_tree et;

	ret = ocfs2_iterate_xattr_buckets(inode, blkno, len,
					  ocfs2_delete_xattr_in_bucket, para);
	if (ret) {
		mlog_errno(ret);
		return ret;
	}

	ocfs2_init_xattr_tree_extent_tree(&et, INODE_CACHE(inode), root_bh);

	ocfs2_init_dealloc_ctxt(&dealloc);

	trace_ocfs2_rm_xattr_cluster(
			(unsigned long long)OCFS2_I(inode)->ip_blkno,
			(unsigned long long)blkno, cpos, len);

	ocfs2_remove_xattr_clusters_from_cache(INODE_CACHE(inode), blkno,
					       len);

	ret = ocfs2_lock_allocators(inode, &et, 0, 1, NULL, &meta_ac);
	if (ret) {
		mlog_errno(ret);
		return ret;
	}

	inode_lock(tl_inode);

	if (ocfs2_truncate_log_needs_flush(osb)) {
		ret = __ocfs2_flush_truncate_log(osb);
		if (ret < 0) {
			mlog_errno(ret);
			goto out;
		}
	}

	handle = ocfs2_start_trans(osb, ocfs2_remove_extent_credits(osb->sb));
	if (IS_ERR(handle)) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_journal_access_xb(handle, INODE_CACHE(inode), root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	ret = ocfs2_remove_extent(handle, &et, cpos, len, meta_ac,
				  &dealloc);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	le32_add_cpu(&xb->xb_attrs.xb_root.xt_clusters, -len);
	ocfs2_journal_dirty(handle, root_bh);

	ret = ocfs2_truncate_log_append(osb, handle, blkno, len);
	if (ret)
		mlog_errno(ret);
	ocfs2_update_inode_fsync_trans(handle, inode, 0);

out_commit:
	ocfs2_commit_trans(osb, handle);
out:
	ocfs2_schedule_truncate_log_flush(osb, 1);

	inode_unlock(tl_inode);

	if (meta_ac)
		ocfs2_free_alloc_context(meta_ac);

	ocfs2_run_deallocs(osb, &dealloc);

	return ret;
}