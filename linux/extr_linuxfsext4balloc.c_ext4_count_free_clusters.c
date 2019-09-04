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
struct ext4_group_info {int dummy; } ;
struct ext4_group_desc {int dummy; } ;
typedef  scalar_t__ ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_2__ {scalar_t__ s_group_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_MB_GRP_BBITMAP_CORRUPT (struct ext4_group_info*) ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 scalar_t__ ext4_free_group_clusters (struct super_block*,struct ext4_group_desc*) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 
 struct ext4_group_info* ext4_get_group_info (struct super_block*,scalar_t__) ; 
 scalar_t__ ext4_get_groups_count (struct super_block*) ; 

ext4_fsblk_t ext4_count_free_clusters(struct super_block *sb)
{
	ext4_fsblk_t desc_count;
	struct ext4_group_desc *gdp;
	ext4_group_t i;
	ext4_group_t ngroups = ext4_get_groups_count(sb);
	struct ext4_group_info *grp;
#ifdef EXT4FS_DEBUG
	struct ext4_super_block *es;
	ext4_fsblk_t bitmap_count;
	unsigned int x;
	struct buffer_head *bitmap_bh = NULL;

	es = EXT4_SB(sb)->s_es;
	desc_count = 0;
	bitmap_count = 0;
	gdp = NULL;

	for (i = 0; i < ngroups; i++) {
		gdp = ext4_get_group_desc(sb, i, NULL);
		if (!gdp)
			continue;
		grp = NULL;
		if (EXT4_SB(sb)->s_group_info)
			grp = ext4_get_group_info(sb, i);
		if (!grp || !EXT4_MB_GRP_BBITMAP_CORRUPT(grp))
			desc_count += ext4_free_group_clusters(sb, gdp);
		brelse(bitmap_bh);
		bitmap_bh = ext4_read_block_bitmap(sb, i);
		if (IS_ERR(bitmap_bh)) {
			bitmap_bh = NULL;
			continue;
		}

		x = ext4_count_free(bitmap_bh->b_data,
				    EXT4_CLUSTERS_PER_GROUP(sb) / 8);
		printk(KERN_DEBUG "group %u: stored = %d, counted = %u\n",
			i, ext4_free_group_clusters(sb, gdp), x);
		bitmap_count += x;
	}
	brelse(bitmap_bh);
	printk(KERN_DEBUG "ext4_count_free_clusters: stored = %llu"
	       ", computed = %llu, %llu\n",
	       EXT4_NUM_B2C(EXT4_SB(sb), ext4_free_blocks_count(es)),
	       desc_count, bitmap_count);
	return bitmap_count;
#else
	desc_count = 0;
	for (i = 0; i < ngroups; i++) {
		gdp = ext4_get_group_desc(sb, i, NULL);
		if (!gdp)
			continue;
		grp = NULL;
		if (EXT4_SB(sb)->s_group_info)
			grp = ext4_get_group_info(sb, i);
		if (!grp || !EXT4_MB_GRP_BBITMAP_CORRUPT(grp))
			desc_count += ext4_free_group_clusters(sb, gdp);
	}

	return desc_count;
#endif
}