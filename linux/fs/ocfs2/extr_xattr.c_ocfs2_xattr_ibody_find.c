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
struct ocfs2_xattr_search {int not_found; struct ocfs2_xattr_header* header; int /*<<< orphan*/  here; void* base; void* end; TYPE_1__* inode_bh; TYPE_1__* xattr_bh; } ;
struct ocfs2_xattr_header {int /*<<< orphan*/  xh_entries; } ;
struct ocfs2_inode_info {int ip_dyn_features; int /*<<< orphan*/  ip_alloc_sem; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_xattr_inline_size; } ;
struct inode {TYPE_3__* i_sb; } ;
struct TYPE_6__ {scalar_t__ s_blocksize; } ;
struct TYPE_5__ {int s_xattr_inline_size; } ;
struct TYPE_4__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENODATA ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_XATTR_FL ; 
 scalar_t__ OCFS2_MIN_BLOCKSIZE ; 
 TYPE_2__* OCFS2_SB (TYPE_3__*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int ocfs2_xattr_find_entry (int,char const*,struct ocfs2_xattr_search*) ; 
 int ocfs2_xattr_has_space_inline (struct inode*,struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_xattr_ibody_find(struct inode *inode,
				  int name_index,
				  const char *name,
				  struct ocfs2_xattr_search *xs)
{
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)xs->inode_bh->b_data;
	int ret;
	int has_space = 0;

	if (inode->i_sb->s_blocksize == OCFS2_MIN_BLOCKSIZE)
		return 0;

	if (!(oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL)) {
		down_read(&oi->ip_alloc_sem);
		has_space = ocfs2_xattr_has_space_inline(inode, di);
		up_read(&oi->ip_alloc_sem);
		if (!has_space)
			return 0;
	}

	xs->xattr_bh = xs->inode_bh;
	xs->end = (void *)di + inode->i_sb->s_blocksize;
	if (oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL)
		xs->header = (struct ocfs2_xattr_header *)
			(xs->end - le16_to_cpu(di->i_xattr_inline_size));
	else
		xs->header = (struct ocfs2_xattr_header *)
			(xs->end - OCFS2_SB(inode->i_sb)->s_xattr_inline_size);
	xs->base = (void *)xs->header;
	xs->here = xs->header->xh_entries;

	/* Find the named attribute. */
	if (oi->ip_dyn_features & OCFS2_INLINE_XATTR_FL) {
		ret = ocfs2_xattr_find_entry(name_index, name, xs);
		if (ret && ret != -ENODATA)
			return ret;
		xs->not_found = ret;
	}

	return 0;
}