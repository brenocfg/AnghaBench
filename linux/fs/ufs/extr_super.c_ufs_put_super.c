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
struct ufs_sb_info {struct ufs_sb_info* s_uspi; int /*<<< orphan*/  sync_work; } ;
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  UFSD (char*) ; 
 struct ufs_sb_info* UFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ufs_sb_info*) ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  ubh_brelse_uspi (struct ufs_sb_info*) ; 
 int /*<<< orphan*/  ufs_put_super_internal (struct super_block*) ; 

__attribute__((used)) static void ufs_put_super(struct super_block *sb)
{
	struct ufs_sb_info * sbi = UFS_SB(sb);

	UFSD("ENTER\n");

	if (!sb_rdonly(sb))
		ufs_put_super_internal(sb);
	cancel_delayed_work_sync(&sbi->sync_work);

	ubh_brelse_uspi (sbi->s_uspi);
	kfree (sbi->s_uspi);
	kfree (sbi);
	sb->s_fs_info = NULL;
	UFSD("EXIT\n");
	return;
}