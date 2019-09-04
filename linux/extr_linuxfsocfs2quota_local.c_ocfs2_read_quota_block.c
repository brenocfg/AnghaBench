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
typedef  scalar_t__ u64 ;
struct inode {TYPE_1__* i_sb; } ;
struct buffer_head {int dummy; } ;
struct TYPE_4__ {scalar_t__ ip_blkno; } ;
struct TYPE_3__ {scalar_t__ s_blocksize_bits; } ;

/* Variables and functions */
 TYPE_2__* OCFS2_I (struct inode*) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_error (TYPE_1__*,char*,unsigned long long,unsigned long long,unsigned long long) ; 
 int ocfs2_read_virt_blocks (struct inode*,scalar_t__,int,struct buffer_head**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_validate_quota_block ; 

__attribute__((used)) static int ocfs2_read_quota_block(struct inode *inode, u64 v_block,
				  struct buffer_head **bh)
{
	int rc = 0;
	struct buffer_head *tmp = *bh;

	if (i_size_read(inode) >> inode->i_sb->s_blocksize_bits <= v_block)
		return ocfs2_error(inode->i_sb,
				"Quota file %llu is probably corrupted! Requested to read block %Lu but file has size only %Lu\n",
				(unsigned long long)OCFS2_I(inode)->ip_blkno,
				(unsigned long long)v_block,
				(unsigned long long)i_size_read(inode));

	rc = ocfs2_read_virt_blocks(inode, v_block, 1, &tmp, 0,
				    ocfs2_validate_quota_block);
	if (rc)
		mlog_errno(rc);

	/* If ocfs2_read_virt_blocks() got us a new bh, pass it up. */
	if (!rc && !*bh)
		*bh = tmp;

	return rc;
}