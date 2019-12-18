#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct ext2_super_block {void* s_rev_level; int /*<<< orphan*/  s_inode_size; void* s_first_ino; } ;
struct TYPE_2__ {struct ext2_super_block* s_es; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2_DYNAMIC_REV ; 
 int /*<<< orphan*/  EXT2_GOOD_OLD_FIRST_INO ; 
 int /*<<< orphan*/  EXT2_GOOD_OLD_INODE_SIZE ; 
 scalar_t__ EXT2_GOOD_OLD_REV ; 
 TYPE_1__* EXT2_SB (struct super_block*) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_msg (struct super_block*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (void*) ; 

void ext2_update_dynamic_rev(struct super_block *sb)
{
	struct ext2_super_block *es = EXT2_SB(sb)->s_es;

	if (le32_to_cpu(es->s_rev_level) > EXT2_GOOD_OLD_REV)
		return;

	ext2_msg(sb, KERN_WARNING,
		     "warning: updating to rev %d because of "
		     "new feature flag, running e2fsck is recommended",
		     EXT2_DYNAMIC_REV);

	es->s_first_ino = cpu_to_le32(EXT2_GOOD_OLD_FIRST_INO);
	es->s_inode_size = cpu_to_le16(EXT2_GOOD_OLD_INODE_SIZE);
	es->s_rev_level = cpu_to_le32(EXT2_DYNAMIC_REV);
	/* leave es->s_feature_*compat flags alone */
	/* es->s_uuid will be set by e2fsck if empty */

	/*
	 * The rest of the superblock fields should be zero, and if not it
	 * means they are likely already in use, so leave them alone.  We
	 * can leave it up to e2fsck to clean up any inconsistencies there.
	 */
}