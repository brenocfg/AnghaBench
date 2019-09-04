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
struct msdos_sb_info {int /*<<< orphan*/  rcu; int /*<<< orphan*/  fat_inode; int /*<<< orphan*/  fsinfo_inode; } ;

/* Variables and functions */
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delayed_free ; 
 int /*<<< orphan*/  fat_set_state (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fat_put_super(struct super_block *sb)
{
	struct msdos_sb_info *sbi = MSDOS_SB(sb);

	fat_set_state(sb, 0, 0);

	iput(sbi->fsinfo_inode);
	iput(sbi->fat_inode);

	call_rcu(&sbi->rcu, delayed_free);
}