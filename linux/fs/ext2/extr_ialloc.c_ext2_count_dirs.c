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
struct ext2_group_desc {int /*<<< orphan*/  bg_used_dirs_count; } ;
struct TYPE_2__ {int s_groups_count; } ;

/* Variables and functions */
 TYPE_1__* EXT2_SB (struct super_block*) ; 
 struct ext2_group_desc* ext2_get_group_desc (struct super_block*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

unsigned long ext2_count_dirs (struct super_block * sb)
{
	unsigned long count = 0;
	int i;

	for (i = 0; i < EXT2_SB(sb)->s_groups_count; i++) {
		struct ext2_group_desc *gdp = ext2_get_group_desc (sb, i, NULL);
		if (!gdp)
			continue;
		count += le16_to_cpu(gdp->bg_used_dirs_count);
	}
	return count;
}