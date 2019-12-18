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
struct kiocb {int dummy; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ F2FS_IO_ALIGNED (struct f2fs_sb_info*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  IS_SWAPFILE (struct inode*) ; 
 int /*<<< orphan*/  LFS ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 int WRITE ; 
 scalar_t__ block_unaligned_IO (struct inode*,struct kiocb*,struct iov_iter*) ; 
 scalar_t__ f2fs_is_multi_device (struct f2fs_sb_info*) ; 
 scalar_t__ f2fs_post_read_required (struct inode*) ; 
 scalar_t__ f2fs_sb_has_blkzoned (struct f2fs_sb_info*) ; 
 int iov_iter_rw (struct iov_iter*) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool f2fs_force_buffered_io(struct inode *inode,
				struct kiocb *iocb, struct iov_iter *iter)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	int rw = iov_iter_rw(iter);

	if (f2fs_post_read_required(inode))
		return true;
	if (f2fs_is_multi_device(sbi))
		return true;
	/*
	 * for blkzoned device, fallback direct IO to buffered IO, so
	 * all IOs can be serialized by log-structured write.
	 */
	if (f2fs_sb_has_blkzoned(sbi))
		return true;
	if (test_opt(sbi, LFS) && (rw == WRITE)) {
		if (block_unaligned_IO(inode, iocb, iter))
			return true;
		if (F2FS_IO_ALIGNED(sbi))
			return true;
	}
	if (is_sbi_flag_set(F2FS_I_SB(inode), SBI_CP_DISABLED) &&
					!IS_SWAPFILE(inode))
		return true;

	return false;
}