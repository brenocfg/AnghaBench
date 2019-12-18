#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_blocksize_bits; } ;
struct ocfs2_xattr_value_buf {scalar_t__ vb_bh; int /*<<< orphan*/  vb_access; } ;
struct ocfs2_xattr_bucket {scalar_t__* bu_bhs; } ;
struct ocfs2_xa_loc {TYPE_2__* xl_entry; TYPE_1__* xl_inode; struct ocfs2_xattr_bucket* xl_storage; } ;
struct TYPE_4__ {int /*<<< orphan*/  xe_name_offset; } ;
struct TYPE_3__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int namevalue_size_xe (TYPE_2__*) ; 
 int /*<<< orphan*/  ocfs2_journal_access ; 

__attribute__((used)) static void ocfs2_xa_bucket_fill_value_buf(struct ocfs2_xa_loc *loc,
					   struct ocfs2_xattr_value_buf *vb)
{
	struct ocfs2_xattr_bucket *bucket = loc->xl_storage;
	struct super_block *sb = loc->xl_inode->i_sb;
	int nameval_offset = le16_to_cpu(loc->xl_entry->xe_name_offset);
	int size = namevalue_size_xe(loc->xl_entry);
	int block_offset = nameval_offset >> sb->s_blocksize_bits;

	/* Values are not allowed to straddle block boundaries */
	BUG_ON(block_offset !=
	       ((nameval_offset + size - 1) >> sb->s_blocksize_bits));
	/* We expect the bucket to be filled in */
	BUG_ON(!bucket->bu_bhs[block_offset]);

	vb->vb_access = ocfs2_journal_access;
	vb->vb_bh = bucket->bu_bhs[block_offset];
}