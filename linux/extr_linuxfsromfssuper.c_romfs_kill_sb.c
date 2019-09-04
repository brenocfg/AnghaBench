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

/* Variables and functions */

__attribute__((used)) static void romfs_kill_sb(struct super_block *sb)
{
#ifdef CONFIG_ROMFS_ON_MTD
	if (sb->s_mtd) {
		kill_mtd_super(sb);
		return;
	}
#endif
#ifdef CONFIG_ROMFS_ON_BLOCK
	if (sb->s_bdev) {
		kill_block_super(sb);
		return;
	}
#endif
}