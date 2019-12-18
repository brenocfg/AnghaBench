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
struct f2fs_sb_info {int /*<<< orphan*/  cp_lock; } ;
struct TYPE_2__ {unsigned char* nat_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_NAT_BITS_FLAG ; 
 int /*<<< orphan*/  F2FS_CKPT (struct f2fs_sb_info*) ; 
 TYPE_1__* NM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __clear_ckpt_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (unsigned char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void disable_nat_bits(struct f2fs_sb_info *sbi, bool lock)
{
	unsigned long flags;
	unsigned char *nat_bits;

	/*
	 * In order to re-enable nat_bits we need to call fsck.f2fs by
	 * set_sbi_flag(sbi, SBI_NEED_FSCK). But it may give huge cost,
	 * so let's rely on regular fsck or unclean shutdown.
	 */

	if (lock)
		spin_lock_irqsave(&sbi->cp_lock, flags);
	__clear_ckpt_flags(F2FS_CKPT(sbi), CP_NAT_BITS_FLAG);
	nat_bits = NM_I(sbi)->nat_bits;
	NM_I(sbi)->nat_bits = NULL;
	if (lock)
		spin_unlock_irqrestore(&sbi->cp_lock, flags);

	kvfree(nat_bits);
}