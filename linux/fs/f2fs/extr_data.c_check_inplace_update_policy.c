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
struct inode {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_io_info {scalar_t__ op; int op_flags; int /*<<< orphan*/  old_blkaddr; } ;
struct TYPE_2__ {unsigned int ipu_policy; scalar_t__ min_ipu_util; } ;

/* Variables and functions */
 int F2FS_IPU_ASYNC ; 
 int F2FS_IPU_FORCE ; 
 int F2FS_IPU_FSYNC ; 
 int F2FS_IPU_SSR ; 
 int F2FS_IPU_SSR_UTIL ; 
 int F2FS_IPU_UTIL ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_NEED_IPU ; 
 int /*<<< orphan*/  IS_ENCRYPTED (struct inode*) ; 
 scalar_t__ REQ_OP_WRITE ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_is_checkpointed_data (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ f2fs_need_SSR (struct f2fs_sb_info*) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ utilization (struct f2fs_sb_info*) ; 

__attribute__((used)) static inline bool check_inplace_update_policy(struct inode *inode,
				struct f2fs_io_info *fio)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	unsigned int policy = SM_I(sbi)->ipu_policy;

	if (policy & (0x1 << F2FS_IPU_FORCE))
		return true;
	if (policy & (0x1 << F2FS_IPU_SSR) && f2fs_need_SSR(sbi))
		return true;
	if (policy & (0x1 << F2FS_IPU_UTIL) &&
			utilization(sbi) > SM_I(sbi)->min_ipu_util)
		return true;
	if (policy & (0x1 << F2FS_IPU_SSR_UTIL) && f2fs_need_SSR(sbi) &&
			utilization(sbi) > SM_I(sbi)->min_ipu_util)
		return true;

	/*
	 * IPU for rewrite async pages
	 */
	if (policy & (0x1 << F2FS_IPU_ASYNC) &&
			fio && fio->op == REQ_OP_WRITE &&
			!(fio->op_flags & REQ_SYNC) &&
			!IS_ENCRYPTED(inode))
		return true;

	/* this is only set during fdatasync */
	if (policy & (0x1 << F2FS_IPU_FSYNC) &&
			is_inode_flag_set(inode, FI_NEED_IPU))
		return true;

	if (unlikely(fio && is_sbi_flag_set(sbi, SBI_CP_DISABLED) &&
			!f2fs_is_checkpointed_data(sbi, fio->old_blkaddr)))
		return true;

	return false;
}