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
struct ext4_sb_info {int s_itb_per_group; TYPE_1__* s_es; } ;
struct ext4_group_desc {int dummy; } ;
typedef  scalar_t__ ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_first_data_block; } ;

/* Variables and functions */
 int EXT4_B2C (struct ext4_sb_info*,scalar_t__) ; 
 int EXT4_BLOCKS_PER_GROUP (struct super_block*) ; 
 int EXT4_CLUSTERS_PER_GROUP (struct super_block*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int ext4_bg_has_super (struct super_block*,scalar_t__) ; 
 int ext4_bg_num_gdb (struct super_block*,scalar_t__) ; 
 scalar_t__ ext4_block_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 int ext4_count_free (char*,int) ; 
 int /*<<< orphan*/  ext4_error (struct super_block*,char*,int) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ext4_get_groups_count (struct super_block*) ; 
 int /*<<< orphan*/  ext4_has_feature_bigalloc (struct super_block*) ; 
 scalar_t__ ext4_inode_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 scalar_t__ ext4_inode_table (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_set_bit (int,char*) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int count_overhead(struct super_block *sb, ext4_group_t grp,
			  char *buf)
{
	struct ext4_sb_info	*sbi = EXT4_SB(sb);
	struct ext4_group_desc	*gdp;
	ext4_fsblk_t		first_block, last_block, b;
	ext4_group_t		i, ngroups = ext4_get_groups_count(sb);
	int			s, j, count = 0;

	if (!ext4_has_feature_bigalloc(sb))
		return (ext4_bg_has_super(sb, grp) + ext4_bg_num_gdb(sb, grp) +
			sbi->s_itb_per_group + 2);

	first_block = le32_to_cpu(sbi->s_es->s_first_data_block) +
		(grp * EXT4_BLOCKS_PER_GROUP(sb));
	last_block = first_block + EXT4_BLOCKS_PER_GROUP(sb) - 1;
	for (i = 0; i < ngroups; i++) {
		gdp = ext4_get_group_desc(sb, i, NULL);
		b = ext4_block_bitmap(sb, gdp);
		if (b >= first_block && b <= last_block) {
			ext4_set_bit(EXT4_B2C(sbi, b - first_block), buf);
			count++;
		}
		b = ext4_inode_bitmap(sb, gdp);
		if (b >= first_block && b <= last_block) {
			ext4_set_bit(EXT4_B2C(sbi, b - first_block), buf);
			count++;
		}
		b = ext4_inode_table(sb, gdp);
		if (b >= first_block && b + sbi->s_itb_per_group <= last_block)
			for (j = 0; j < sbi->s_itb_per_group; j++, b++) {
				int c = EXT4_B2C(sbi, b - first_block);
				ext4_set_bit(c, buf);
				count++;
			}
		if (i != grp)
			continue;
		s = 0;
		if (ext4_bg_has_super(sb, grp)) {
			ext4_set_bit(s++, buf);
			count++;
		}
		j = ext4_bg_num_gdb(sb, grp);
		if (s + j > EXT4_BLOCKS_PER_GROUP(sb)) {
			ext4_error(sb, "Invalid number of block group "
				   "descriptor blocks: %d", j);
			j = EXT4_BLOCKS_PER_GROUP(sb) - s;
		}
		count += j;
		for (; j > 0; j--)
			ext4_set_bit(EXT4_B2C(sbi, s++), buf);
	}
	if (!count)
		return 0;
	return EXT4_CLUSTERS_PER_GROUP(sb) -
		ext4_count_free(buf, EXT4_CLUSTERS_PER_GROUP(sb) / 8);
}