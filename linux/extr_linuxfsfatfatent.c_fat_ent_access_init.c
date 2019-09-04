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
struct msdos_sb_info {int fat_bits; int fatent_shift; int /*<<< orphan*/ * fatent_ops; int /*<<< orphan*/  fat_lock; } ;

/* Variables and functions */
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  fat12_ops ; 
 int /*<<< orphan*/  fat16_ops ; 
 int /*<<< orphan*/  fat32_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void fat_ent_access_init(struct super_block *sb)
{
	struct msdos_sb_info *sbi = MSDOS_SB(sb);

	mutex_init(&sbi->fat_lock);

	switch (sbi->fat_bits) {
	case 32:
		sbi->fatent_shift = 2;
		sbi->fatent_ops = &fat32_ops;
		break;
	case 16:
		sbi->fatent_shift = 1;
		sbi->fatent_ops = &fat16_ops;
		break;
	case 12:
		sbi->fatent_shift = -1;
		sbi->fatent_ops = &fat12_ops;
		break;
	}
}