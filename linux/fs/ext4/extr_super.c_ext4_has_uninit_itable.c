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
struct ext4_group_desc {int bg_flags; } ;
typedef  scalar_t__ ext4_group_t ;
struct TYPE_2__ {scalar_t__ s_groups_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_BG_INODE_ZEROED ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_has_group_desc_csum (struct super_block*) ; 

__attribute__((used)) static ext4_group_t ext4_has_uninit_itable(struct super_block *sb)
{
	ext4_group_t group, ngroups = EXT4_SB(sb)->s_groups_count;
	struct ext4_group_desc *gdp = NULL;

	if (!ext4_has_group_desc_csum(sb))
		return ngroups;

	for (group = 0; group < ngroups; group++) {
		gdp = ext4_get_group_desc(sb, group, NULL);
		if (!gdp)
			continue;

		if (!(gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_ZEROED)))
			break;
	}

	return group;
}