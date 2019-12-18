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
struct super_block {scalar_t__ s_magic; int /*<<< orphan*/ * s_fs_info; } ;
struct erofs_sb_info {int dummy; } ;

/* Variables and functions */
 struct erofs_sb_info* EROFS_SB (struct super_block*) ; 
 scalar_t__ EROFS_SUPER_MAGIC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct erofs_sb_info*) ; 
 int /*<<< orphan*/  kill_block_super (struct super_block*) ; 

__attribute__((used)) static void erofs_kill_sb(struct super_block *sb)
{
	struct erofs_sb_info *sbi;

	WARN_ON(sb->s_magic != EROFS_SUPER_MAGIC);

	kill_block_super(sb);

	sbi = EROFS_SB(sb);
	if (!sbi)
		return;
	kfree(sbi);
	sb->s_fs_info = NULL;
}