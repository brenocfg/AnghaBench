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
struct ext2_super_block {int s_state; } ;
struct ext2_sb_info {int /*<<< orphan*/  s_lock; struct ext2_super_block* s_es; } ;

/* Variables and functions */
 struct ext2_sb_info* EXT2_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT2_VALID_FS ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dquot_writeback_dquots (struct super_block*,int) ; 
 int /*<<< orphan*/  ext2_debug (char*) ; 
 int /*<<< orphan*/  ext2_sync_super (struct super_block*,struct ext2_super_block*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext2_sync_fs(struct super_block *sb, int wait)
{
	struct ext2_sb_info *sbi = EXT2_SB(sb);
	struct ext2_super_block *es = EXT2_SB(sb)->s_es;

	/*
	 * Write quota structures to quota file, sync_blockdev() will write
	 * them to disk later
	 */
	dquot_writeback_dquots(sb, -1);

	spin_lock(&sbi->s_lock);
	if (es->s_state & cpu_to_le16(EXT2_VALID_FS)) {
		ext2_debug("setting valid to 0\n");
		es->s_state &= cpu_to_le16(~EXT2_VALID_FS);
	}
	spin_unlock(&sbi->s_lock);
	ext2_sync_super(sb, es, wait);
	return 0;
}