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
typedef  int ext4_group_t ;
typedef  int ext4_fsblk_t ;
struct TYPE_4__ {TYPE_1__* s_es; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_first_data_block; } ;

/* Variables and functions */
 int EXT4_BLOCK_SIZE_BITS (struct super_block*) ; 
 int EXT4_CLUSTER_BITS (struct super_block*) ; 
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  STD_GROUP_SIZE ; 
 int /*<<< orphan*/  ext4_get_group_no_and_offset (struct super_block*,int,int*,int /*<<< orphan*/ *) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt2 (struct super_block*,int /*<<< orphan*/ ) ; 

ext4_group_t ext4_get_group_number(struct super_block *sb,
				   ext4_fsblk_t block)
{
	ext4_group_t group;

	if (test_opt2(sb, STD_GROUP_SIZE))
		group = (block -
			 le32_to_cpu(EXT4_SB(sb)->s_es->s_first_data_block)) >>
			(EXT4_BLOCK_SIZE_BITS(sb) + EXT4_CLUSTER_BITS(sb) + 3);
	else
		ext4_get_group_no_and_offset(sb, block, &group, NULL);
	return group;
}