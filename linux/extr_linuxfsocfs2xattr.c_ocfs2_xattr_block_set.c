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
struct ocfs2_xattr_set_ctxt {scalar_t__ set_abort; } ;
struct ocfs2_xattr_search {int /*<<< orphan*/ * here; scalar_t__ not_found; struct buffer_head* xattr_bh; TYPE_3__* header; void* end; void* base; int /*<<< orphan*/  inode_bh; } ;
struct ocfs2_xattr_info {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * xh_entries; } ;
struct TYPE_4__ {TYPE_3__ xb_header; } ;
struct ocfs2_xattr_block {int /*<<< orphan*/  xb_flags; TYPE_1__ xb_attrs; } ;
struct ocfs2_xa_loc {int /*<<< orphan*/ * xl_entry; } ;
struct inode {TYPE_2__* i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_5__ {int s_blocksize; } ;

/* Variables and functions */
 int ENOSPC ; 
 int OCFS2_XATTR_INDEXED ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_create_xattr_block (struct inode*,int /*<<< orphan*/ ,struct ocfs2_xattr_set_ctxt*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  ocfs2_init_xattr_block_xa_loc (struct ocfs2_xa_loc*,struct inode*,struct buffer_head*,int /*<<< orphan*/ *) ; 
 int ocfs2_xa_set (struct ocfs2_xa_loc*,struct ocfs2_xattr_info*,struct ocfs2_xattr_set_ctxt*) ; 
 int ocfs2_xattr_create_index_block (struct inode*,struct ocfs2_xattr_search*,struct ocfs2_xattr_set_ctxt*) ; 
 int ocfs2_xattr_set_entry_index_block (struct inode*,struct ocfs2_xattr_info*,struct ocfs2_xattr_search*,struct ocfs2_xattr_set_ctxt*) ; 

__attribute__((used)) static int ocfs2_xattr_block_set(struct inode *inode,
				 struct ocfs2_xattr_info *xi,
				 struct ocfs2_xattr_search *xs,
				 struct ocfs2_xattr_set_ctxt *ctxt)
{
	struct buffer_head *new_bh = NULL;
	struct ocfs2_xattr_block *xblk = NULL;
	int ret;
	struct ocfs2_xa_loc loc;

	if (!xs->xattr_bh) {
		ret = ocfs2_create_xattr_block(inode, xs->inode_bh, ctxt,
					       0, &new_bh);
		if (ret) {
			mlog_errno(ret);
			goto end;
		}

		xs->xattr_bh = new_bh;
		xblk = (struct ocfs2_xattr_block *)xs->xattr_bh->b_data;
		xs->header = &xblk->xb_attrs.xb_header;
		xs->base = (void *)xs->header;
		xs->end = (void *)xblk + inode->i_sb->s_blocksize;
		xs->here = xs->header->xh_entries;
	} else
		xblk = (struct ocfs2_xattr_block *)xs->xattr_bh->b_data;

	if (!(le16_to_cpu(xblk->xb_flags) & OCFS2_XATTR_INDEXED)) {
		ocfs2_init_xattr_block_xa_loc(&loc, inode, xs->xattr_bh,
					      xs->not_found ? NULL : xs->here);

		ret = ocfs2_xa_set(&loc, xi, ctxt);
		if (!ret)
			xs->here = loc.xl_entry;
		else if ((ret != -ENOSPC) || ctxt->set_abort)
			goto end;
		else {
			ret = ocfs2_xattr_create_index_block(inode, xs, ctxt);
			if (ret)
				goto end;
		}
	}

	if (le16_to_cpu(xblk->xb_flags) & OCFS2_XATTR_INDEXED)
		ret = ocfs2_xattr_set_entry_index_block(inode, xi, xs, ctxt);

end:
	return ret;
}