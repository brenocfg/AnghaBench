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
struct efs_sb_info {int dummy; } ;

/* Variables and functions */
 struct efs_sb_info* SUPER_INFO (struct super_block*) ; 
 int /*<<< orphan*/  kfree (struct efs_sb_info*) ; 
 int /*<<< orphan*/  kill_block_super (struct super_block*) ; 

__attribute__((used)) static void efs_kill_sb(struct super_block *s)
{
	struct efs_sb_info *sbi = SUPER_INFO(s);
	kill_block_super(s);
	kfree(sbi);
}