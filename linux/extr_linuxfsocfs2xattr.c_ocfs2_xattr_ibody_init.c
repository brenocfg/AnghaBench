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
struct ocfs2_xattr_set_ctxt {int /*<<< orphan*/  handle; } ;
struct ocfs2_super {unsigned int s_xattr_inline_size; } ;
struct ocfs2_inode_info {int ip_dyn_features; int /*<<< orphan*/  ip_lock; } ;
struct ocfs2_inline_data {int /*<<< orphan*/  id_count; } ;
struct ocfs2_extent_rec {int dummy; } ;
struct ocfs2_extent_list {int /*<<< orphan*/  l_count; } ;
struct TYPE_2__ {struct ocfs2_extent_list i_list; struct ocfs2_inline_data i_data; } ;
struct ocfs2_dinode {void* i_dyn_features; void* i_xattr_inline_size; TYPE_1__ id2; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int OCFS2_HAS_XATTR_FL ; 
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 int OCFS2_INLINE_XATTR_FL ; 
 int /*<<< orphan*/  OCFS2_JOURNAL_ACCESS_WRITE ; 
 struct ocfs2_super* OCFS2_SB (int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_inode_is_fast_symlink (struct inode*) ; 
 int ocfs2_journal_access_di (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_xattr_has_space_inline (struct inode*,struct ocfs2_dinode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_xattr_ibody_init(struct inode *inode,
				  struct buffer_head *di_bh,
				  struct ocfs2_xattr_set_ctxt *ctxt)
{
	int ret;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)di_bh->b_data;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	unsigned int xattrsize = osb->s_xattr_inline_size;

	if (!ocfs2_xattr_has_space_inline(inode, di)) {
		ret = -ENOSPC;
		goto out;
	}

	ret = ocfs2_journal_access_di(ctxt->handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	/*
	 * Adjust extent record count or inline data size
	 * to reserve space for extended attribute.
	 */
	if (oi->ip_dyn_features & OCFS2_INLINE_DATA_FL) {
		struct ocfs2_inline_data *idata = &di->id2.i_data;
		le16_add_cpu(&idata->id_count, -xattrsize);
	} else if (!(ocfs2_inode_is_fast_symlink(inode))) {
		struct ocfs2_extent_list *el = &di->id2.i_list;
		le16_add_cpu(&el->l_count, -(xattrsize /
					     sizeof(struct ocfs2_extent_rec)));
	}
	di->i_xattr_inline_size = cpu_to_le16(xattrsize);

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features |= OCFS2_INLINE_XATTR_FL|OCFS2_HAS_XATTR_FL;
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	spin_unlock(&oi->ip_lock);

	ocfs2_journal_dirty(ctxt->handle, di_bh);

out:
	return ret;
}