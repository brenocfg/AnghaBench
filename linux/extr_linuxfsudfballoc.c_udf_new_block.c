#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t uint16_t ;
typedef  scalar_t__ udf_pblk_t ;
struct TYPE_5__ {int /*<<< orphan*/  s_table; int /*<<< orphan*/  s_bitmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_table; int /*<<< orphan*/  s_bitmap; } ;
struct udf_part_map {int s_partition_flags; TYPE_2__ s_fspace; TYPE_1__ s_uspace; } ;
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {struct udf_part_map* s_partmaps; } ;

/* Variables and functions */
 int EIO ; 
 int UDF_PART_FLAG_FREED_BITMAP ; 
 int UDF_PART_FLAG_FREED_TABLE ; 
 int UDF_PART_FLAG_UNALLOC_BITMAP ; 
 int UDF_PART_FLAG_UNALLOC_TABLE ; 
 TYPE_3__* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  inode_add_bytes (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ udf_bitmap_new_block (struct super_block*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ udf_table_new_block (struct super_block*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int*) ; 

inline udf_pblk_t udf_new_block(struct super_block *sb,
			 struct inode *inode,
			 uint16_t partition, uint32_t goal, int *err)
{
	struct udf_part_map *map = &UDF_SB(sb)->s_partmaps[partition];
	udf_pblk_t block;

	if (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_BITMAP)
		block = udf_bitmap_new_block(sb,
					     map->s_uspace.s_bitmap,
					     partition, goal, err);
	else if (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_TABLE)
		block = udf_table_new_block(sb,
					    map->s_uspace.s_table,
					    partition, goal, err);
	else if (map->s_partition_flags & UDF_PART_FLAG_FREED_BITMAP)
		block = udf_bitmap_new_block(sb,
					     map->s_fspace.s_bitmap,
					     partition, goal, err);
	else if (map->s_partition_flags & UDF_PART_FLAG_FREED_TABLE)
		block = udf_table_new_block(sb,
					    map->s_fspace.s_table,
					    partition, goal, err);
	else {
		*err = -EIO;
		return 0;
	}
	if (inode && block)
		inode_add_bytes(inode, sb->s_blocksize);
	return block;
}