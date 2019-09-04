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
struct list_head {int dummy; } ;
struct ext4_group_desc {int dummy; } ;
typedef  scalar_t__ ext4_group_t ;
struct TYPE_2__ {scalar_t__ s_groups_count; int s_itb_per_group; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int /*<<< orphan*/  EXT4_FMR_OWN_BLKBM ; 
 int /*<<< orphan*/  EXT4_FMR_OWN_INOBM ; 
 int /*<<< orphan*/  EXT4_FMR_OWN_INODES ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  ext4_block_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_getfsmap_compare ; 
 int ext4_getfsmap_fill (struct list_head*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ext4_getfsmap_find_sb (struct super_block*,scalar_t__,struct list_head*) ; 
 int /*<<< orphan*/  ext4_getfsmap_free_fixed_metadata (struct list_head*) ; 
 int /*<<< orphan*/  ext4_getfsmap_merge_fixed_metadata (struct list_head*) ; 
 int /*<<< orphan*/  ext4_inode_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_inode_table (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  list_sort (int /*<<< orphan*/ *,struct list_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_getfsmap_find_fixed_metadata(struct super_block *sb,
					     struct list_head *meta_list)
{
	struct ext4_group_desc *gdp;
	ext4_group_t agno;
	int error;

	INIT_LIST_HEAD(meta_list);

	/* Collect everything. */
	for (agno = 0; agno < EXT4_SB(sb)->s_groups_count; agno++) {
		gdp = ext4_get_group_desc(sb, agno, NULL);
		if (!gdp) {
			error = -EFSCORRUPTED;
			goto err;
		}

		/* Superblock & GDT */
		error = ext4_getfsmap_find_sb(sb, agno, meta_list);
		if (error)
			goto err;

		/* Block bitmap */
		error = ext4_getfsmap_fill(meta_list,
					   ext4_block_bitmap(sb, gdp), 1,
					   EXT4_FMR_OWN_BLKBM);
		if (error)
			goto err;

		/* Inode bitmap */
		error = ext4_getfsmap_fill(meta_list,
					   ext4_inode_bitmap(sb, gdp), 1,
					   EXT4_FMR_OWN_INOBM);
		if (error)
			goto err;

		/* Inodes */
		error = ext4_getfsmap_fill(meta_list,
					   ext4_inode_table(sb, gdp),
					   EXT4_SB(sb)->s_itb_per_group,
					   EXT4_FMR_OWN_INODES);
		if (error)
			goto err;
	}

	/* Sort the list */
	list_sort(NULL, meta_list, ext4_getfsmap_compare);

	/* Merge adjacent extents */
	ext4_getfsmap_merge_fixed_metadata(meta_list);

	return 0;
err:
	ext4_getfsmap_free_fixed_metadata(meta_list);
	return error;
}