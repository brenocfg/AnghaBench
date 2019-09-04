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
struct page {int dummy; } ;
struct f2fs_checkpoint {int dummy; } ;
typedef  int __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CP_CRC_RECOVERY_FLAG ; 
 int /*<<< orphan*/  CP_NOCRC_RECOVERY_FLAG ; 
 struct f2fs_checkpoint* F2FS_CKPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F2FS_P_SB (struct page*) ; 
 scalar_t__ __is_set_ckpt_flags (struct f2fs_checkpoint*,int /*<<< orphan*/ ) ; 
 int cpver_of_node (struct page*) ; 
 int cur_cp_crc (struct f2fs_checkpoint*) ; 
 int cur_cp_version (struct f2fs_checkpoint*) ; 

__attribute__((used)) static inline bool is_recoverable_dnode(struct page *page)
{
	struct f2fs_checkpoint *ckpt = F2FS_CKPT(F2FS_P_SB(page));
	__u64 cp_ver = cur_cp_version(ckpt);

	/* Don't care crc part, if fsck.f2fs sets it. */
	if (__is_set_ckpt_flags(ckpt, CP_NOCRC_RECOVERY_FLAG))
		return (cp_ver << 32) == (cpver_of_node(page) << 32);

	if (__is_set_ckpt_flags(ckpt, CP_CRC_RECOVERY_FLAG))
		cp_ver |= (cur_cp_crc(ckpt) << 32);

	return cp_ver == cpver_of_node(page);
}