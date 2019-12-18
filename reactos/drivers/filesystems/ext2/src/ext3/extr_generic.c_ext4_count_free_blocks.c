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
struct ext4_group_desc {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_2__ {scalar_t__ s_groups_count; } ;

/* Variables and functions */
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 scalar_t__ ext4_free_blks_count (struct super_block*,struct ext4_group_desc*) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,scalar_t__,struct buffer_head**) ; 
 int /*<<< orphan*/  fini_bh (struct buffer_head**) ; 
 int /*<<< orphan*/  smp_rmb () ; 

ext4_fsblk_t ext4_count_free_blocks(struct super_block *sb)
{
    ext4_fsblk_t desc_count;
    struct ext4_group_desc *gdp;
    struct buffer_head *bh = NULL;
    ext4_group_t i;
    ext4_group_t ngroups = EXT3_SB(sb)->s_groups_count;

    desc_count = 0;
    smp_rmb();
    for (i = 0; i < ngroups; i++) {
        gdp = ext4_get_group_desc(sb, i, &bh);
        if (!bh)
            continue;
        desc_count += ext4_free_blks_count(sb, gdp);
        fini_bh(&bh);
    }

    return desc_count;
}