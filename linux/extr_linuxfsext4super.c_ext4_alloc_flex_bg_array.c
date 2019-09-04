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
struct flex_groups {int dummy; } ;
struct ext4_sb_info {int s_flex_groups_allocated; struct flex_groups* s_flex_groups; int /*<<< orphan*/  s_log_groups_per_flex; } ;
typedef  scalar_t__ ext4_group_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int ext4_flex_group (struct ext4_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kvfree (struct flex_groups*) ; 
 struct flex_groups* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct flex_groups*,struct flex_groups*,int) ; 
 int roundup_pow_of_two (int) ; 

int ext4_alloc_flex_bg_array(struct super_block *sb, ext4_group_t ngroup)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct flex_groups *new_groups;
	int size;

	if (!sbi->s_log_groups_per_flex)
		return 0;

	size = ext4_flex_group(sbi, ngroup - 1) + 1;
	if (size <= sbi->s_flex_groups_allocated)
		return 0;

	size = roundup_pow_of_two(size * sizeof(struct flex_groups));
	new_groups = kvzalloc(size, GFP_KERNEL);
	if (!new_groups) {
		ext4_msg(sb, KERN_ERR, "not enough memory for %d flex groups",
			 size / (int) sizeof(struct flex_groups));
		return -ENOMEM;
	}

	if (sbi->s_flex_groups) {
		memcpy(new_groups, sbi->s_flex_groups,
		       (sbi->s_flex_groups_allocated *
			sizeof(struct flex_groups)));
		kvfree(sbi->s_flex_groups);
	}
	sbi->s_flex_groups = new_groups;
	sbi->s_flex_groups_allocated = size / sizeof(struct flex_groups);
	return 0;
}