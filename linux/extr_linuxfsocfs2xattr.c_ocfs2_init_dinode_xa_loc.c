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
struct ocfs2_xattr_header {int dummy; } ;
struct ocfs2_xattr_entry {int dummy; } ;
struct ocfs2_xa_loc {scalar_t__ xl_size; struct ocfs2_xattr_header* xl_header; struct ocfs2_xattr_entry* xl_entry; struct buffer_head* xl_storage; int /*<<< orphan*/ * xl_ops; struct inode* xl_inode; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_xattr_inline_size; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_size; scalar_t__ b_data; } ;
struct TYPE_2__ {int ip_dyn_features; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_XATTR_FL ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xa_block_loc_ops ; 

__attribute__((used)) static void ocfs2_init_dinode_xa_loc(struct ocfs2_xa_loc *loc,
				     struct inode *inode,
				     struct buffer_head *bh,
				     struct ocfs2_xattr_entry *entry)
{
	struct ocfs2_dinode *di = (struct ocfs2_dinode *)bh->b_data;

	BUG_ON(!(OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_XATTR_FL));

	loc->xl_inode = inode;
	loc->xl_ops = &ocfs2_xa_block_loc_ops;
	loc->xl_storage = bh;
	loc->xl_entry = entry;
	loc->xl_size = le16_to_cpu(di->i_xattr_inline_size);
	loc->xl_header =
		(struct ocfs2_xattr_header *)(bh->b_data + bh->b_size -
					      loc->xl_size);
}