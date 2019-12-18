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
struct ocfs2_write_ctxt {int /*<<< orphan*/  w_first_new_cpos; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;
typedef  unsigned int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 unsigned int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_clusters_for_bytes (int /*<<< orphan*/ ,unsigned int) ; 
 int ocfs2_extend_no_holes (struct inode*,struct buffer_head*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ocfs2_sparse_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_expand_nonsparse_inode(struct inode *inode,
					struct buffer_head *di_bh,
					loff_t pos, unsigned len,
					struct ocfs2_write_ctxt *wc)
{
	int ret;
	loff_t newsize = pos + len;

	BUG_ON(ocfs2_sparse_alloc(OCFS2_SB(inode->i_sb)));

	if (newsize <= i_size_read(inode))
		return 0;

	ret = ocfs2_extend_no_holes(inode, di_bh, newsize, pos);
	if (ret)
		mlog_errno(ret);

	/* There is no wc if this is call from direct. */
	if (wc)
		wc->w_first_new_cpos =
			ocfs2_clusters_for_bytes(inode->i_sb, i_size_read(inode));

	return ret;
}