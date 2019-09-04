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
struct ocfs2_super {int dummy; } ;
struct ocfs2_refcount_tree {int /*<<< orphan*/  rf_ci; } ;
struct ocfs2_refcount_block {int dummy; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_refcount_loc; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {int ip_dyn_features; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 scalar_t__ ocfs2_dealloc_has_cluster (struct ocfs2_cached_dealloc_ctxt*) ; 
 int ocfs2_duplicate_extent_list (struct inode*,struct inode*,struct buffer_head*,int /*<<< orphan*/ *,struct buffer_head*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int ocfs2_duplicate_inline_data (struct inode*,struct buffer_head*,struct inode*,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_init_dealloc_ctxt (struct ocfs2_cached_dealloc_ctxt*) ; 
 int ocfs2_lock_refcount_tree (struct ocfs2_super*,int /*<<< orphan*/ ,int,struct ocfs2_refcount_tree**,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_run_deallocs (struct ocfs2_super*,struct ocfs2_cached_dealloc_ctxt*) ; 
 int /*<<< orphan*/  ocfs2_schedule_truncate_log_flush (struct ocfs2_super*,int) ; 
 int ocfs2_set_refcount_tree (struct inode*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_unlock_refcount_tree (struct ocfs2_super*,struct ocfs2_refcount_tree*,int) ; 

__attribute__((used)) static int ocfs2_create_reflink_node(struct inode *s_inode,
				     struct buffer_head *s_bh,
				     struct inode *t_inode,
				     struct buffer_head *t_bh,
				     bool preserve)
{
	int ret;
	struct buffer_head *ref_root_bh = NULL;
	struct ocfs2_cached_dealloc_ctxt dealloc;
	struct ocfs2_super *osb = OCFS2_SB(s_inode->i_sb);
	struct ocfs2_refcount_block *rb;
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)s_bh->b_data;
	struct ocfs2_refcount_tree *ref_tree;

	ocfs2_init_dealloc_ctxt(&dealloc);

	ret = ocfs2_set_refcount_tree(t_inode, t_bh,
				      le64_to_cpu(di->i_refcount_loc));
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	if (OCFS2_I(s_inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
		ret = ocfs2_duplicate_inline_data(s_inode, s_bh,
						  t_inode, t_bh);
		if (ret)
			mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_lock_refcount_tree(osb, le64_to_cpu(di->i_refcount_loc),
				       1, &ref_tree, &ref_root_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}
	rb = (struct ocfs2_refcount_block *)ref_root_bh->b_data;

	ret = ocfs2_duplicate_extent_list(s_inode, t_inode, t_bh,
					  &ref_tree->rf_ci, ref_root_bh,
					  &dealloc);
	if (ret) {
		mlog_errno(ret);
		goto out_unlock_refcount;
	}

out_unlock_refcount:
	ocfs2_unlock_refcount_tree(osb, ref_tree, 1);
	brelse(ref_root_bh);
out:
	if (ocfs2_dealloc_has_cluster(&dealloc)) {
		ocfs2_schedule_truncate_log_flush(osb, 1);
		ocfs2_run_deallocs(osb, &dealloc);
	}

	return ret;
}