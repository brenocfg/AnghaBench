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
struct super_block {int dummy; } ;
struct msdos_sb_info {int fatent_shift; int /*<<< orphan*/  fat_bits; int /*<<< orphan*/ * fatent_ops; int /*<<< orphan*/  fat_lock; } ;

/* Variables and functions */
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  fat12_ops ; 
 int /*<<< orphan*/  fat16_ops ; 
 int /*<<< orphan*/  fat32_ops ; 
 int /*<<< orphan*/  fat_fs_error (struct super_block*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_fat12 (struct msdos_sb_info*) ; 
 scalar_t__ is_fat16 (struct msdos_sb_info*) ; 
 scalar_t__ is_fat32 (struct msdos_sb_info*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void fat_ent_access_init(struct super_block *sb)
{
	struct msdos_sb_info *sbi = MSDOS_SB(sb);

	mutex_init(&sbi->fat_lock);

	if (is_fat32(sbi)) {
		sbi->fatent_shift = 2;
		sbi->fatent_ops = &fat32_ops;
	} else if (is_fat16(sbi)) {
		sbi->fatent_shift = 1;
		sbi->fatent_ops = &fat16_ops;
	} else if (is_fat12(sbi)) {
		sbi->fatent_shift = -1;
		sbi->fatent_ops = &fat12_ops;
	} else {
		fat_fs_error(sb, "invalid FAT variant, %u bits", sbi->fat_bits);
	}
}