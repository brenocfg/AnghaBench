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
struct ocfs2_super {int dummy; } ;
struct ocfs2_refcount_tree {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_list; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_refcount_loc; TYPE_1__ id2; } ;
struct ocfs2_cow_context {int /*<<< orphan*/  data_et; int /*<<< orphan*/  get_clusters; int /*<<< orphan*/  cow_duplicate_clusters; struct buffer_head* ref_root_bh; struct ocfs2_refcount_tree* ref_tree; scalar_t__ cow_len; scalar_t__ cow_start; struct inode* inode; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip_blkno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 TYPE_2__* OCFS2_I (struct inode*) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  kfree (struct ocfs2_cow_context*) ; 
 struct ocfs2_cow_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_di_get_clusters ; 
 int /*<<< orphan*/  ocfs2_duplicate_clusters_by_page ; 
 int /*<<< orphan*/  ocfs2_extent_map_trunc (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_init_dinode_extent_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_is_refcount_inode (struct inode*) ; 
 int ocfs2_lock_refcount_tree (struct ocfs2_super*,int /*<<< orphan*/ ,int,struct ocfs2_refcount_tree**,struct buffer_head**) ; 
 int ocfs2_refcount_cal_cow_clusters (struct inode*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int ocfs2_replace_cow (struct ocfs2_cow_context*) ; 
 int /*<<< orphan*/  ocfs2_unlock_refcount_tree (struct ocfs2_super*,struct ocfs2_refcount_tree*,int) ; 
 int /*<<< orphan*/  trace_ocfs2_refcount_cow_hunk (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ocfs2_refcount_cow_hunk(struct inode *inode,
				   struct buffer_head *di_bh,
				   u32 cpos, u32 write_len, u32 max_cpos)
{
	int ret;
	u32 cow_start = 0, cow_len = 0;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)di_bh->b_data;
	struct buffer_head *ref_root_bh = NULL;
	struct ocfs2_refcount_tree *ref_tree;
	struct ocfs2_cow_context *context = NULL;

	BUG_ON(!ocfs2_is_refcount_inode(inode));

	ret = ocfs2_refcount_cal_cow_clusters(inode, &di->id2.i_list,
					      cpos, write_len, max_cpos,
					      &cow_start, &cow_len);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	trace_ocfs2_refcount_cow_hunk(OCFS2_I(inode)->ip_blkno,
				      cpos, write_len, max_cpos,
				      cow_start, cow_len);

	BUG_ON(cow_len == 0);

	context = kzalloc(sizeof(struct ocfs2_cow_context), GFP_NOFS);
	if (!context) {
		ret = -ENOMEM;
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_lock_refcount_tree(osb, le64_to_cpu(di->i_refcount_loc),
				       1, &ref_tree, &ref_root_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	context->inode = inode;
	context->cow_start = cow_start;
	context->cow_len = cow_len;
	context->ref_tree = ref_tree;
	context->ref_root_bh = ref_root_bh;
	context->cow_duplicate_clusters = ocfs2_duplicate_clusters_by_page;
	context->get_clusters = ocfs2_di_get_clusters;

	ocfs2_init_dinode_extent_tree(&context->data_et,
				      INODE_CACHE(inode), di_bh);

	ret = ocfs2_replace_cow(context);
	if (ret)
		mlog_errno(ret);

	/*
	 * truncate the extent map here since no matter whether we meet with
	 * any error during the action, we shouldn't trust cached extent map
	 * any more.
	 */
	ocfs2_extent_map_trunc(inode, cow_start);

	ocfs2_unlock_refcount_tree(osb, ref_tree, 1);
	brelse(ref_root_bh);
out:
	kfree(context);
	return ret;
}