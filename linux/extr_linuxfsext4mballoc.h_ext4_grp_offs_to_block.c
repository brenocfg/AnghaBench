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
struct ext4_free_extent {int fe_start; int /*<<< orphan*/  fe_group; } ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_2__ {int s_cluster_bits; } ;

/* Variables and functions */
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 scalar_t__ ext4_group_first_block_no (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ext4_fsblk_t ext4_grp_offs_to_block(struct super_block *sb,
					struct ext4_free_extent *fex)
{
	return ext4_group_first_block_no(sb, fex->fe_group) +
		(fex->fe_start << EXT4_SB(sb)->s_cluster_bits);
}