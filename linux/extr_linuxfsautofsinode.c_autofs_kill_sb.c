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
struct autofs_sb_info {int /*<<< orphan*/  oz_pgrp; } ;

/* Variables and functions */
 int /*<<< orphan*/  autofs_catatonic_mode (struct autofs_sb_info*) ; 
 struct autofs_sb_info* autofs_sbi (struct super_block*) ; 
 int /*<<< orphan*/  kfree_rcu (struct autofs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_litter_super (struct super_block*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 

void autofs_kill_sb(struct super_block *sb)
{
	struct autofs_sb_info *sbi = autofs_sbi(sb);

	/*
	 * In the event of a failure in get_sb_nodev the superblock
	 * info is not present so nothing else has been setup, so
	 * just call kill_anon_super when we are called from
	 * deactivate_super.
	 */
	if (sbi) {
		/* Free wait queues, close pipe */
		autofs_catatonic_mode(sbi);
		put_pid(sbi->oz_pgrp);
	}

	pr_debug("shutting down\n");
	kill_litter_super(sb);
	if (sbi)
		kfree_rcu(sbi, rcu);
}