#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {int i_ino; } ;
struct ext2_group_desc {int /*<<< orphan*/  bg_free_inodes_count; int /*<<< orphan*/  bg_free_blocks_count; } ;
struct TYPE_4__ {int i_block_group; } ;
struct TYPE_3__ {int s_groups_count; } ;

/* Variables and functions */
 TYPE_2__* EXT2_I (struct inode*) ; 
 TYPE_1__* EXT2_SB (struct super_block*) ; 
 struct ext2_group_desc* ext2_get_group_desc (struct super_block*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_group_other(struct super_block *sb, struct inode *parent)
{
	int parent_group = EXT2_I(parent)->i_block_group;
	int ngroups = EXT2_SB(sb)->s_groups_count;
	struct ext2_group_desc *desc;
	int group, i;

	/*
	 * Try to place the inode in its parent directory
	 */
	group = parent_group;
	desc = ext2_get_group_desc (sb, group, NULL);
	if (desc && le16_to_cpu(desc->bg_free_inodes_count) &&
			le16_to_cpu(desc->bg_free_blocks_count))
		goto found;

	/*
	 * We're going to place this inode in a different blockgroup from its
	 * parent.  We want to cause files in a common directory to all land in
	 * the same blockgroup.  But we want files which are in a different
	 * directory which shares a blockgroup with our parent to land in a
	 * different blockgroup.
	 *
	 * So add our directory's i_ino into the starting point for the hash.
	 */
	group = (group + parent->i_ino) % ngroups;

	/*
	 * Use a quadratic hash to find a group with a free inode and some
	 * free blocks.
	 */
	for (i = 1; i < ngroups; i <<= 1) {
		group += i;
		if (group >= ngroups)
			group -= ngroups;
		desc = ext2_get_group_desc (sb, group, NULL);
		if (desc && le16_to_cpu(desc->bg_free_inodes_count) &&
				le16_to_cpu(desc->bg_free_blocks_count))
			goto found;
	}

	/*
	 * That failed: try linear search for a free inode, even if that group
	 * has no free blocks.
	 */
	group = parent_group;
	for (i = 0; i < ngroups; i++) {
		if (++group >= ngroups)
			group = 0;
		desc = ext2_get_group_desc (sb, group, NULL);
		if (desc && le16_to_cpu(desc->bg_free_inodes_count))
			goto found;
	}

	return -1;

found:
	return group;
}