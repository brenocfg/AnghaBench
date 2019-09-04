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
struct affs_sb_info {int /*<<< orphan*/  s_bmlock; struct affs_sb_info* s_prefix; int /*<<< orphan*/  s_root_bh; } ;

/* Variables and functions */
 struct affs_sb_info* AFFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  affs_brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_free_bitmap (struct super_block*) ; 
 int /*<<< orphan*/  kfree (struct affs_sb_info*) ; 
 int /*<<< orphan*/  kill_block_super (struct super_block*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void affs_kill_sb(struct super_block *sb)
{
	struct affs_sb_info *sbi = AFFS_SB(sb);
	kill_block_super(sb);
	if (sbi) {
		affs_free_bitmap(sb);
		affs_brelse(sbi->s_root_bh);
		kfree(sbi->s_prefix);
		mutex_destroy(&sbi->s_bmlock);
		kfree(sbi);
	}
}