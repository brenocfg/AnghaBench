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
struct ocfs2_xattr_set_ctxt {int dummy; } ;
struct ocfs2_xattr_search {int not_found; int /*<<< orphan*/  xattr_bh; int /*<<< orphan*/  bucket; } ;
struct ocfs2_xattr_info {int /*<<< orphan*/  xi_name; int /*<<< orphan*/  xi_name_index; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int ENOSPC ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_add_new_xattr_bucket (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_xattr_set_ctxt*) ; 
 int ocfs2_check_xattr_bucket_collision (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_relse (int /*<<< orphan*/ ) ; 
 int ocfs2_xattr_index_block_find (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ocfs2_xattr_search*) ; 
 int ocfs2_xattr_set_entry_bucket (struct inode*,struct ocfs2_xattr_info*,struct ocfs2_xattr_search*,struct ocfs2_xattr_set_ctxt*) ; 
 int /*<<< orphan*/  trace_ocfs2_xattr_set_entry_index_block (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_xattr_set_entry_index_block(struct inode *inode,
					     struct ocfs2_xattr_info *xi,
					     struct ocfs2_xattr_search *xs,
					     struct ocfs2_xattr_set_ctxt *ctxt)
{
	int ret;

	trace_ocfs2_xattr_set_entry_index_block(xi->xi_name);

	ret = ocfs2_xattr_set_entry_bucket(inode, xi, xs, ctxt);
	if (!ret)
		goto out;
	if (ret != -ENOSPC) {
		mlog_errno(ret);
		goto out;
	}

	/* Ack, need more space.  Let's try to get another bucket! */

	/*
	 * We do not allow for overlapping ranges between buckets. And
	 * the maximum number of collisions we will allow for then is
	 * one bucket's worth, so check it here whether we need to
	 * add a new bucket for the insert.
	 */
	ret = ocfs2_check_xattr_bucket_collision(inode,
						 xs->bucket,
						 xi->xi_name);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_add_new_xattr_bucket(inode,
					 xs->xattr_bh,
					 xs->bucket,
					 ctxt);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/*
	 * ocfs2_add_new_xattr_bucket() will have updated
	 * xs->bucket if it moved, but it will not have updated
	 * any of the other search fields.  Thus, we drop it and
	 * re-search.  Everything should be cached, so it'll be
	 * quick.
	 */
	ocfs2_xattr_bucket_relse(xs->bucket);
	ret = ocfs2_xattr_index_block_find(inode, xs->xattr_bh,
					   xi->xi_name_index,
					   xi->xi_name, xs);
	if (ret && ret != -ENODATA)
		goto out;
	xs->not_found = ret;

	/* Ok, we have a new bucket, let's try again */
	ret = ocfs2_xattr_set_entry_bucket(inode, xi, xs, ctxt);
	if (ret && (ret != -ENOSPC))
		mlog_errno(ret);

out:
	return ret;
}