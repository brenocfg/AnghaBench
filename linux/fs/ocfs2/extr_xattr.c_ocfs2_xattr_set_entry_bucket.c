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
struct ocfs2_xattr_set_ctxt {int /*<<< orphan*/  handle; } ;
struct ocfs2_xattr_search {int /*<<< orphan*/ * here; int /*<<< orphan*/  bucket; scalar_t__ not_found; } ;
struct ocfs2_xattr_info {int /*<<< orphan*/  xi_name; } ;
struct ocfs2_xa_loc {int /*<<< orphan*/ * xl_entry; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_defrag_xattr_bucket (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_init_xattr_bucket_xa_loc (struct ocfs2_xa_loc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ocfs2_xa_set (struct ocfs2_xa_loc*,struct ocfs2_xattr_info*,struct ocfs2_xattr_set_ctxt*) ; 
 int /*<<< orphan*/  trace_ocfs2_xattr_set_entry_bucket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_xattr_set_entry_bucket(struct inode *inode,
					struct ocfs2_xattr_info *xi,
					struct ocfs2_xattr_search *xs,
					struct ocfs2_xattr_set_ctxt *ctxt)
{
	int ret;
	struct ocfs2_xa_loc loc;

	trace_ocfs2_xattr_set_entry_bucket(xi->xi_name);

	ocfs2_init_xattr_bucket_xa_loc(&loc, xs->bucket,
				       xs->not_found ? NULL : xs->here);
	ret = ocfs2_xa_set(&loc, xi, ctxt);
	if (!ret) {
		xs->here = loc.xl_entry;
		goto out;
	}
	if (ret != -ENOSPC) {
		mlog_errno(ret);
		goto out;
	}

	/* Ok, we need space.  Let's try defragmenting the bucket. */
	ret = ocfs2_defrag_xattr_bucket(inode, ctxt->handle,
					xs->bucket);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_xa_set(&loc, xi, ctxt);
	if (!ret) {
		xs->here = loc.xl_entry;
		goto out;
	}
	if (ret != -ENOSPC)
		mlog_errno(ret);


out:
	return ret;
}