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
struct ext2_group_desc {int /*<<< orphan*/  bg_free_blocks_count; } ;
struct TYPE_2__ {int s_groups_count; } ;

/* Variables and functions */
 TYPE_1__* EXT2_SB (struct super_block*) ; 
 struct ext2_group_desc* ext2_get_group_desc (struct super_block*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

unsigned long ext2_count_free_blocks (struct super_block * sb)
{
	struct ext2_group_desc * desc;
	unsigned long desc_count = 0;
	int i;
#ifdef EXT2FS_DEBUG
	unsigned long bitmap_count, x;
	struct ext2_super_block *es;

	es = EXT2_SB(sb)->s_es;
	desc_count = 0;
	bitmap_count = 0;
	desc = NULL;
	for (i = 0; i < EXT2_SB(sb)->s_groups_count; i++) {
		struct buffer_head *bitmap_bh;
		desc = ext2_get_group_desc (sb, i, NULL);
		if (!desc)
			continue;
		desc_count += le16_to_cpu(desc->bg_free_blocks_count);
		bitmap_bh = read_block_bitmap(sb, i);
		if (!bitmap_bh)
			continue;
		
		x = ext2_count_free(bitmap_bh, sb->s_blocksize);
		printk ("group %d: stored = %d, counted = %lu\n",
			i, le16_to_cpu(desc->bg_free_blocks_count), x);
		bitmap_count += x;
		brelse(bitmap_bh);
	}
	printk("ext2_count_free_blocks: stored = %lu, computed = %lu, %lu\n",
		(long)le32_to_cpu(es->s_free_blocks_count),
		desc_count, bitmap_count);
	return bitmap_count;
#else
        for (i = 0; i < EXT2_SB(sb)->s_groups_count; i++) {
                desc = ext2_get_group_desc (sb, i, NULL);
                if (!desc)
                        continue;
                desc_count += le16_to_cpu(desc->bg_free_blocks_count);
	}
	return desc_count;
#endif
}