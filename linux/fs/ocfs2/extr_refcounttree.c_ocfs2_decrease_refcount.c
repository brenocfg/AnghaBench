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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_refcount_tree {int /*<<< orphan*/  rf_ci; int /*<<< orphan*/  rf_blkno; } ;
struct ocfs2_cached_dealloc_ctxt {int dummy; } ;
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int __ocfs2_decrease_refcount (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_alloc_context*,struct ocfs2_cached_dealloc_ctxt*,int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_get_refcount_block (struct inode*,int /*<<< orphan*/ *) ; 
 int ocfs2_get_refcount_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_refcount_tree**) ; 
 int /*<<< orphan*/  ocfs2_is_refcount_inode (struct inode*) ; 
 int ocfs2_read_refcount_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct buffer_head**) ; 

int ocfs2_decrease_refcount(struct inode *inode,
			    handle_t *handle, u32 cpos, u32 len,
			    struct ocfs2_alloc_context *meta_ac,
			    struct ocfs2_cached_dealloc_ctxt *dealloc,
			    int delete)
{
	int ret;
	u64 ref_blkno;
	struct buffer_head *ref_root_bh = NULL;
	struct ocfs2_refcount_tree *tree;

	BUG_ON(!ocfs2_is_refcount_inode(inode));

	ret = ocfs2_get_refcount_block(inode, &ref_blkno);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_get_refcount_tree(OCFS2_SB(inode->i_sb), ref_blkno, &tree);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_read_refcount_block(&tree->rf_ci, tree->rf_blkno,
					&ref_root_bh);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = __ocfs2_decrease_refcount(handle, &tree->rf_ci, ref_root_bh,
					cpos, len, meta_ac, dealloc, delete);
	if (ret)
		mlog_errno(ret);
out:
	brelse(ref_root_bh);
	return ret;
}