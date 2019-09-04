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
struct ext4_group_desc {int dummy; } ;
typedef  scalar_t__ ext4_group_t ;

/* Variables and functions */
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_get_groups_count (struct super_block*) ; 
 scalar_t__ ext4_used_dirs_count (struct super_block*,struct ext4_group_desc*) ; 

unsigned long ext4_count_dirs(struct super_block * sb)
{
	unsigned long count = 0;
	ext4_group_t i, ngroups = ext4_get_groups_count(sb);

	for (i = 0; i < ngroups; i++) {
		struct ext4_group_desc *gdp = ext4_get_group_desc(sb, i, NULL);
		if (!gdp)
			continue;
		count += ext4_used_dirs_count(sb, gdp);
	}
	return count;
}