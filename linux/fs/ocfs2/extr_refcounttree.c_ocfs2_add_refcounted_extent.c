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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int /*<<< orphan*/  sb; } ;
struct ocfs2_extent_tree {int dummy; } ;
struct ocfs2_caching_info {int dummy; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int dquot_alloc_space_nodirty (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_clusters_to_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (struct ocfs2_alloc_context*) ; 
 int ocfs2_increase_refcount (int /*<<< orphan*/ *,struct ocfs2_caching_info*,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int ocfs2_insert_extent (int /*<<< orphan*/ *,struct ocfs2_extent_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,struct ocfs2_alloc_context*) ; 
 int ocfs2_lock_refcount_allocators (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_extent_tree*,struct ocfs2_caching_info*,struct buffer_head*,struct ocfs2_alloc_context**,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * ocfs2_start_trans (struct ocfs2_super*,int) ; 

__attribute__((used)) static int ocfs2_add_refcounted_extent(struct inode *inode,
				   struct ocfs2_extent_tree *et,
				   struct ocfs2_caching_info *ref_ci,
				   struct buffer_head *ref_root_bh,
				   u32 cpos, u32 p_cluster, u32 num_clusters,
				   unsigned int ext_flags,
				   struct ocfs2_cached_dealloc_ctxt *dealloc)
{
	int ret;
	handle_t *handle;
	int credits = 0;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_alloc_context *meta_ac = NULL;

	ret = ocfs2_lock_refcount_allocators(inode->i_sb,
					     p_cluster, num_clusters,
					     et, ref_ci,
					     ref_root_bh, &meta_ac,
					     NULL, &credits);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	handle = ocfs2_start_trans(osb, credits);
	if (IS_ERR(handle)) {
		ret = PTR_ERR(handle);
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_insert_extent(handle, et, cpos,
			ocfs2_clusters_to_blocks(inode->i_sb, p_cluster),
			num_clusters, ext_flags, meta_ac);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	ret = ocfs2_increase_refcount(handle, ref_ci, ref_root_bh,
				      p_cluster, num_clusters,
				      meta_ac, dealloc);
	if (ret) {
		mlog_errno(ret);
		goto out_commit;
	}

	ret = dquot_alloc_space_nodirty(inode,
		ocfs2_clusters_to_bytes(osb->sb, num_clusters));
	if (ret)
		mlog_errno(ret);

out_commit:
	ocfs2_commit_trans(osb, handle);
out:
	if (meta_ac)
		ocfs2_free_alloc_context(meta_ac);
	return ret;
}