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
struct ocfs2_xattr_set_ctxt {int /*<<< orphan*/  meta_ac; int /*<<< orphan*/  handle; } ;
struct ocfs2_super {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_blocknr; } ;
typedef  int /*<<< orphan*/  ctxt ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCFS2_XATTR_BLOCK_CREATE_CREDITS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_xattr_set_ctxt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_commit_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int ocfs2_create_xattr_block (struct inode*,struct buffer_head*,struct ocfs2_xattr_set_ctxt*,int,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_free_alloc_context (int /*<<< orphan*/ ) ; 
 int ocfs2_reserve_new_metadata_blocks (struct ocfs2_super*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_start_trans (struct ocfs2_super*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ocfs2_create_empty_xattr_block (unsigned long long,int) ; 

__attribute__((used)) static int ocfs2_create_empty_xattr_block(struct inode *inode,
					  struct buffer_head *fe_bh,
					  struct buffer_head **ret_bh,
					  int indexed)
{
	int ret;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	struct ocfs2_xattr_set_ctxt ctxt;

	memset(&ctxt, 0, sizeof(ctxt));
	ret = ocfs2_reserve_new_metadata_blocks(osb, 1, &ctxt.meta_ac);
	if (ret < 0) {
		mlog_errno(ret);
		return ret;
	}

	ctxt.handle = ocfs2_start_trans(osb, OCFS2_XATTR_BLOCK_CREATE_CREDITS);
	if (IS_ERR(ctxt.handle)) {
		ret = PTR_ERR(ctxt.handle);
		mlog_errno(ret);
		goto out;
	}

	trace_ocfs2_create_empty_xattr_block(
				(unsigned long long)fe_bh->b_blocknr, indexed);
	ret = ocfs2_create_xattr_block(inode, fe_bh, &ctxt, indexed,
				       ret_bh);
	if (ret)
		mlog_errno(ret);

	ocfs2_commit_trans(osb, ctxt.handle);
out:
	ocfs2_free_alloc_context(ctxt.meta_ac);
	return ret;
}