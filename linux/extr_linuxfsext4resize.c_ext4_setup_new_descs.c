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
struct ext4_sb_info {struct buffer_head** s_group_desc; } ;
struct ext4_new_group_data {int group; int /*<<< orphan*/  free_clusters_count; int /*<<< orphan*/  inode_table; int /*<<< orphan*/  inode_bitmap; int /*<<< orphan*/  block_bitmap; } ;
struct ext4_new_flex_group_data {int count; int /*<<< orphan*/ * bg_flags; struct ext4_new_group_data* groups; } ;
struct ext4_group_desc {int /*<<< orphan*/  bg_flags; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_group_t ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int EXT4_DESC_PER_BLOCK (struct super_block*) ; 
 int EXT4_DESC_SIZE (struct super_block*) ; 
 int /*<<< orphan*/  EXT4_INODES_PER_GROUP (struct super_block*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_block_bitmap_set (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_free_group_clusters_set (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_free_inodes_set (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_group_desc_csum_set (struct super_block*,int,struct ext4_group_desc*) ; 
 int ext4_handle_dirty_metadata (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct buffer_head*) ; 
 scalar_t__ ext4_has_group_desc_csum (struct super_block*) ; 
 int /*<<< orphan*/  ext4_inode_bitmap_set (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_inode_table_set (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_itable_unused_set (struct super_block*,struct ext4_group_desc*,int /*<<< orphan*/ ) ; 
 int ext4_mb_add_groupinfo (struct super_block*,int,struct ext4_group_desc*) ; 
 int ext4_set_bitmap_checksums (struct super_block*,int,struct ext4_group_desc*,struct ext4_new_group_data*) ; 
 int /*<<< orphan*/  ext4_std_error (struct super_block*,int) ; 
 int /*<<< orphan*/  memset (struct ext4_group_desc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ext4_setup_new_descs(handle_t *handle, struct super_block *sb,
				struct ext4_new_flex_group_data *flex_gd)
{
	struct ext4_new_group_data	*group_data = flex_gd->groups;
	struct ext4_group_desc		*gdp;
	struct ext4_sb_info		*sbi = EXT4_SB(sb);
	struct buffer_head		*gdb_bh;
	ext4_group_t			group;
	__u16				*bg_flags = flex_gd->bg_flags;
	int				i, gdb_off, gdb_num, err = 0;


	for (i = 0; i < flex_gd->count; i++, group_data++, bg_flags++) {
		group = group_data->group;

		gdb_off = group % EXT4_DESC_PER_BLOCK(sb);
		gdb_num = group / EXT4_DESC_PER_BLOCK(sb);

		/*
		 * get_write_access() has been called on gdb_bh by ext4_add_new_desc().
		 */
		gdb_bh = sbi->s_group_desc[gdb_num];
		/* Update group descriptor block for new group */
		gdp = (struct ext4_group_desc *)(gdb_bh->b_data +
						 gdb_off * EXT4_DESC_SIZE(sb));

		memset(gdp, 0, EXT4_DESC_SIZE(sb));
		ext4_block_bitmap_set(sb, gdp, group_data->block_bitmap);
		ext4_inode_bitmap_set(sb, gdp, group_data->inode_bitmap);
		err = ext4_set_bitmap_checksums(sb, group, gdp, group_data);
		if (err) {
			ext4_std_error(sb, err);
			break;
		}

		ext4_inode_table_set(sb, gdp, group_data->inode_table);
		ext4_free_group_clusters_set(sb, gdp,
					     group_data->free_clusters_count);
		ext4_free_inodes_set(sb, gdp, EXT4_INODES_PER_GROUP(sb));
		if (ext4_has_group_desc_csum(sb))
			ext4_itable_unused_set(sb, gdp,
					       EXT4_INODES_PER_GROUP(sb));
		gdp->bg_flags = cpu_to_le16(*bg_flags);
		ext4_group_desc_csum_set(sb, group, gdp);

		err = ext4_handle_dirty_metadata(handle, NULL, gdb_bh);
		if (unlikely(err)) {
			ext4_std_error(sb, err);
			break;
		}

		/*
		 * We can allocate memory for mb_alloc based on the new group
		 * descriptor
		 */
		err = ext4_mb_add_groupinfo(sb, group, gdp);
		if (err)
			break;
	}
	return err;
}