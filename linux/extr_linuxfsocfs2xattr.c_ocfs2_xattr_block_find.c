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
struct ocfs2_xattr_search {int not_found; struct buffer_head* xattr_bh; TYPE_3__* header; int /*<<< orphan*/  here; void* end; void* base; TYPE_1__* inode_bh; } ;
struct TYPE_6__ {int /*<<< orphan*/  xh_entries; } ;
struct TYPE_5__ {TYPE_3__ xb_header; } ;
struct ocfs2_xattr_block {TYPE_2__ xb_attrs; int /*<<< orphan*/  xb_flags; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_xattr_loc; } ;
struct inode {int dummy; } ;
struct buffer_head {int b_size; scalar_t__ b_data; } ;
struct TYPE_4__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENODATA ; 
 int OCFS2_XATTR_INDEXED ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_read_xattr_block (struct inode*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int ocfs2_xattr_find_entry (int,char const*,struct ocfs2_xattr_search*) ; 
 int ocfs2_xattr_index_block_find (struct inode*,struct buffer_head*,int,char const*,struct ocfs2_xattr_search*) ; 

__attribute__((used)) static int ocfs2_xattr_block_find(struct inode *inode,
				  int name_index,
				  const char *name,
				  struct ocfs2_xattr_search *xs)
{
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)xs->inode_bh->b_data;
	struct buffer_head *blk_bh = NULL;
	struct ocfs2_xattr_block *xb;
	int ret = 0;

	if (!di->i_xattr_loc)
		return ret;

	ret = ocfs2_read_xattr_block(inode, le64_to_cpu(di->i_xattr_loc),
				     &blk_bh);
	if (ret < 0) {
		mlog_errno(ret);
		return ret;
	}

	xs->xattr_bh = blk_bh;
	xb = (struct ocfs2_xattr_block *)blk_bh->b_data;

	if (!(le16_to_cpu(xb->xb_flags) & OCFS2_XATTR_INDEXED)) {
		xs->header = &xb->xb_attrs.xb_header;
		xs->base = (void *)xs->header;
		xs->end = (void *)(blk_bh->b_data) + blk_bh->b_size;
		xs->here = xs->header->xh_entries;

		ret = ocfs2_xattr_find_entry(name_index, name, xs);
	} else
		ret = ocfs2_xattr_index_block_find(inode, blk_bh,
						   name_index,
						   name, xs);

	if (ret && ret != -ENODATA) {
		xs->xattr_bh = NULL;
		goto cleanup;
	}
	xs->not_found = ret;
	return 0;
cleanup:
	brelse(blk_bh);

	return ret;
}