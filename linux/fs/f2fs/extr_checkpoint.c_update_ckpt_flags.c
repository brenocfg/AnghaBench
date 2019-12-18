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
struct f2fs_sb_info {scalar_t__ blocks_per_seg; int /*<<< orphan*/  cp_lock; TYPE_1__* im; } ;
struct f2fs_checkpoint {int /*<<< orphan*/  cp_pack_total_block_count; } ;
struct cp_control {int reason; } ;
struct TYPE_4__ {scalar_t__ nat_bits_blocks; } ;
struct TYPE_3__ {unsigned long ino_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_CRC_RECOVERY_FLAG ; 
 int /*<<< orphan*/  CP_DISABLED_FLAG ; 
 int /*<<< orphan*/  CP_DISABLED_QUICK_FLAG ; 
 int CP_FASTBOOT ; 
 int /*<<< orphan*/  CP_FASTBOOT_FLAG ; 
 int /*<<< orphan*/  CP_FSCK_FLAG ; 
 int /*<<< orphan*/  CP_NOCRC_RECOVERY_FLAG ; 
 int /*<<< orphan*/  CP_ORPHAN_PRESENT_FLAG ; 
 int /*<<< orphan*/  CP_QUOTA_NEED_FSCK_FLAG ; 
 int CP_TRIMMED ; 
 int /*<<< orphan*/  CP_TRIMMED_FLAG ; 
 int CP_UMOUNT ; 
 int /*<<< orphan*/  CP_UMOUNT_FLAG ; 
 struct f2fs_checkpoint* F2FS_CKPT (struct f2fs_sb_info*) ; 
 TYPE_2__* NM_I (struct f2fs_sb_info*) ; 
 size_t ORPHAN_INO ; 
 int /*<<< orphan*/  SBI_CP_DISABLED ; 
 int /*<<< orphan*/  SBI_CP_DISABLED_QUICK ; 
 int /*<<< orphan*/  SBI_IS_RESIZEFS ; 
 int /*<<< orphan*/  SBI_NEED_FSCK ; 
 int /*<<< orphan*/  SBI_QUOTA_NEED_REPAIR ; 
 int /*<<< orphan*/  SBI_QUOTA_SKIP_FLUSH ; 
 int /*<<< orphan*/  __clear_ckpt_flags (struct f2fs_checkpoint*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_ckpt_flags (struct f2fs_checkpoint*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_nat_bits (struct f2fs_sb_info*,int) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void update_ckpt_flags(struct f2fs_sb_info *sbi, struct cp_control *cpc)
{
	unsigned long orphan_num = sbi->im[ORPHAN_INO].ino_num;
	struct f2fs_checkpoint *ckpt = F2FS_CKPT(sbi);
	unsigned long flags;

	spin_lock_irqsave(&sbi->cp_lock, flags);

	if ((cpc->reason & CP_UMOUNT) &&
			le32_to_cpu(ckpt->cp_pack_total_block_count) >
			sbi->blocks_per_seg - NM_I(sbi)->nat_bits_blocks)
		disable_nat_bits(sbi, false);

	if (cpc->reason & CP_TRIMMED)
		__set_ckpt_flags(ckpt, CP_TRIMMED_FLAG);
	else
		__clear_ckpt_flags(ckpt, CP_TRIMMED_FLAG);

	if (cpc->reason & CP_UMOUNT)
		__set_ckpt_flags(ckpt, CP_UMOUNT_FLAG);
	else
		__clear_ckpt_flags(ckpt, CP_UMOUNT_FLAG);

	if (cpc->reason & CP_FASTBOOT)
		__set_ckpt_flags(ckpt, CP_FASTBOOT_FLAG);
	else
		__clear_ckpt_flags(ckpt, CP_FASTBOOT_FLAG);

	if (orphan_num)
		__set_ckpt_flags(ckpt, CP_ORPHAN_PRESENT_FLAG);
	else
		__clear_ckpt_flags(ckpt, CP_ORPHAN_PRESENT_FLAG);

	if (is_sbi_flag_set(sbi, SBI_NEED_FSCK) ||
		is_sbi_flag_set(sbi, SBI_IS_RESIZEFS))
		__set_ckpt_flags(ckpt, CP_FSCK_FLAG);

	if (is_sbi_flag_set(sbi, SBI_CP_DISABLED))
		__set_ckpt_flags(ckpt, CP_DISABLED_FLAG);
	else
		__clear_ckpt_flags(ckpt, CP_DISABLED_FLAG);

	if (is_sbi_flag_set(sbi, SBI_CP_DISABLED_QUICK))
		__set_ckpt_flags(ckpt, CP_DISABLED_QUICK_FLAG);
	else
		__clear_ckpt_flags(ckpt, CP_DISABLED_QUICK_FLAG);

	if (is_sbi_flag_set(sbi, SBI_QUOTA_SKIP_FLUSH))
		__set_ckpt_flags(ckpt, CP_QUOTA_NEED_FSCK_FLAG);
	else
		__clear_ckpt_flags(ckpt, CP_QUOTA_NEED_FSCK_FLAG);

	if (is_sbi_flag_set(sbi, SBI_QUOTA_NEED_REPAIR))
		__set_ckpt_flags(ckpt, CP_QUOTA_NEED_FSCK_FLAG);

	/* set this flag to activate crc|cp_ver for recovery */
	__set_ckpt_flags(ckpt, CP_CRC_RECOVERY_FLAG);
	__clear_ckpt_flags(ckpt, CP_NOCRC_RECOVERY_FLAG);

	spin_unlock_irqrestore(&sbi->cp_lock, flags);
}