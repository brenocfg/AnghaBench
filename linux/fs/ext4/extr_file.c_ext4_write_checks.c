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
struct kiocb {scalar_t__ ki_pos; int /*<<< orphan*/  ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_sb_info {scalar_t__ s_bitmap_maxbytes; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EFBIG ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  EXT4_INODE_EXTENTS ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_IMMUTABLE (struct inode*) ; 
 int /*<<< orphan*/  ext4_test_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ generic_write_checks (struct kiocb*,struct iov_iter*) ; 
 scalar_t__ iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_truncate (struct iov_iter*,scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ext4_write_checks(struct kiocb *iocb, struct iov_iter *from)
{
	struct inode *inode = file_inode(iocb->ki_filp);
	ssize_t ret;

	ret = generic_write_checks(iocb, from);
	if (ret <= 0)
		return ret;

	if (unlikely(IS_IMMUTABLE(inode)))
		return -EPERM;

	/*
	 * If we have encountered a bitmap-format file, the size limit
	 * is smaller than s_maxbytes, which is for extent-mapped files.
	 */
	if (!(ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS))) {
		struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);

		if (iocb->ki_pos >= sbi->s_bitmap_maxbytes)
			return -EFBIG;
		iov_iter_truncate(from, sbi->s_bitmap_maxbytes - iocb->ki_pos);
	}
	return iov_iter_count(from);
}