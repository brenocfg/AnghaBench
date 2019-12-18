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
struct f2fs_sb_info {int /*<<< orphan*/  cp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_CKPT (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __set_ckpt_flags (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void set_ckpt_flags(struct f2fs_sb_info *sbi, unsigned int f)
{
	unsigned long flags;

	spin_lock_irqsave(&sbi->cp_lock, flags);
	__set_ckpt_flags(F2FS_CKPT(sbi), f);
	spin_unlock_irqrestore(&sbi->cp_lock, flags);
}