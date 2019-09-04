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
struct ocfs2_xattr_set_ctxt {int dummy; } ;
struct ocfs2_xattr_search {int /*<<< orphan*/ * here; scalar_t__ not_found; int /*<<< orphan*/  inode_bh; } ;
struct ocfs2_xattr_info {int dummy; } ;
struct ocfs2_xa_loc {int /*<<< orphan*/ * xl_entry; } ;
struct ocfs2_inode_info {int ip_dyn_features; int /*<<< orphan*/  ip_alloc_sem; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 int ENOSPC ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_XATTR_FL ; 
 scalar_t__ OCFS2_MIN_BLOCKSIZE ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_init_dinode_xa_loc (struct ocfs2_xa_loc*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ocfs2_xa_set (struct ocfs2_xa_loc*,struct ocfs2_xattr_info*,struct ocfs2_xattr_set_ctxt*) ; 
 int ocfs2_xattr_ibody_init (struct inode*,int /*<<< orphan*/ ,struct ocfs2_xattr_set_ctxt*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_xattr_ibody_set(struct inode *inode,
				 struct ocfs2_xattr_info *xi,
				 struct ocfs2_xattr_search *xs,
				 struct ocfs2_xattr_set_ctxt *ctxt)
{
	int ret;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_xa_loc loc;

	if (inode->i_sb->s_blocksize == OCFS2_MIN_BLOCKSIZE)
		return -ENOSPC;

	down_write(&oi->ip_alloc_sem);
	if (!(oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL)) {
		ret = ocfs2_xattr_ibody_init(inode, xs->inode_bh, ctxt);
		if (ret) {
			if (ret != -ENOSPC)
				mlog_errno(ret);
			goto out;
		}
	}

	ocfs2_init_dinode_xa_loc(&loc, inode, xs->inode_bh,
				 xs->not_found ? NULL : xs->here);
	ret = ocfs2_xa_set(&loc, xi, ctxt);
	if (ret) {
		if (ret != -ENOSPC)
			mlog_errno(ret);
		goto out;
	}
	xs->here = loc.xl_entry;

out:
	up_write(&oi->ip_alloc_sem);

	return ret;
}