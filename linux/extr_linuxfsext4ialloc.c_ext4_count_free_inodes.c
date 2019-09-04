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
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ ext4_free_inodes_count (struct super_block*,struct ext4_group_desc*) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_get_groups_count (struct super_block*) ; 

unsigned long ext4_count_free_inodes(struct super_block *sb)
{
	unsigned long desc_count;
	struct ext4_group_desc *gdp;
	ext4_group_t i, ngroups = ext4_get_groups_count(sb);
#ifdef EXT4FS_DEBUG
	struct ext4_super_block *es;
	unsigned long bitmap_count, x;
	struct buffer_head *bitmap_bh = NULL;

	es = EXT4_SB(sb)->s_es;
	desc_count = 0;
	bitmap_count = 0;
	gdp = NULL;
	for (i = 0; i < ngroups; i++) {
		gdp = ext4_get_group_desc(sb, i, NULL);
		if (!gdp)
			continue;
		desc_count += ext4_free_inodes_count(sb, gdp);
		brelse(bitmap_bh);
		bitmap_bh = ext4_read_inode_bitmap(sb, i);
		if (IS_ERR(bitmap_bh)) {
			bitmap_bh = NULL;
			continue;
		}

		x = ext4_count_free(bitmap_bh->b_data,
				    EXT4_INODES_PER_GROUP(sb) / 8);
		printk(KERN_DEBUG "group %lu: stored = %d, counted = %lu\n",
			(unsigned long) i, ext4_free_inodes_count(sb, gdp), x);
		bitmap_count += x;
	}
	brelse(bitmap_bh);
	printk(KERN_DEBUG "ext4_count_free_inodes: "
	       "stored = %u, computed = %lu, %lu\n",
	       le32_to_cpu(es->s_free_inodes_count), desc_count, bitmap_count);
	return desc_count;
#else
	desc_count = 0;
	for (i = 0; i < ngroups; i++) {
		gdp = ext4_get_group_desc(sb, i, NULL);
		if (!gdp)
			continue;
		desc_count += ext4_free_inodes_count(sb, gdp);
		cond_resched();
	}
	return desc_count;
#endif
}