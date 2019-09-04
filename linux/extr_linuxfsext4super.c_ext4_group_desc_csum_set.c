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
struct ext4_group_desc {int /*<<< orphan*/  bg_checksum; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_group_desc_csum (struct super_block*,int /*<<< orphan*/ ,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_has_group_desc_csum (struct super_block*) ; 

void ext4_group_desc_csum_set(struct super_block *sb, __u32 block_group,
			      struct ext4_group_desc *gdp)
{
	if (!ext4_has_group_desc_csum(sb))
		return;
	gdp->bg_checksum = ext4_group_desc_csum(sb, block_group, gdp);
}