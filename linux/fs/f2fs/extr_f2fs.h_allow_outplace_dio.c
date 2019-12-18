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
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  LFS ; 
 int WRITE ; 
 int /*<<< orphan*/  block_unaligned_IO (struct inode*,struct kiocb*,struct iov_iter*) ; 
 int iov_iter_rw (struct iov_iter*) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int allow_outplace_dio(struct inode *inode,
				struct kiocb *iocb, struct iov_iter *iter)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	int rw = iov_iter_rw(iter);

	return (test_opt(sbi, LFS) && (rw == WRITE) &&
				!block_unaligned_IO(inode, iocb, iter));
}