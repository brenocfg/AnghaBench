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
struct super_block {int /*<<< orphan*/  s_id; } ;
struct ext4_sb_info {int /*<<< orphan*/  s_kobj; scalar_t__ s_proc; } ;

/* Variables and functions */
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  ext4_proc_root ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_proc_subtree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ext4_unregister_sysfs(struct super_block *sb)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);

	if (sbi->s_proc)
		remove_proc_subtree(sb->s_id, ext4_proc_root);
	kobject_del(&sbi->s_kobj);
}