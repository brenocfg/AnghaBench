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
struct TYPE_5__ {int /*<<< orphan*/  s_table; int /*<<< orphan*/  s_bitmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_table; int /*<<< orphan*/  s_bitmap; } ;
struct udf_part_map {int s_partition_flags; TYPE_2__ s_fspace; TYPE_1__ s_uspace; } ;
struct super_block {int s_blocksize_bits; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {struct udf_part_map* s_partmaps; } ;

/* Variables and functions */
 int UDF_PART_FLAG_FREED_BITMAP ; 
 int UDF_PART_FLAG_FREED_TABLE ; 
 int UDF_PART_FLAG_UNALLOC_BITMAP ; 
 int UDF_PART_FLAG_UNALLOC_TABLE ; 
 TYPE_3__* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  inode_add_bytes (struct inode*,int) ; 
 int udf_bitmap_prealloc_blocks (struct super_block*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int udf_table_prealloc_blocks (struct super_block*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

inline int udf_prealloc_blocks(struct super_block *sb,
			       struct inode *inode,
			       uint16_t partition, uint32_t first_block,
			       uint32_t block_count)
{
	struct udf_part_map *map = &UDF_SB(sb)->s_partmaps[partition];
	int allocated;

	if (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_BITMAP)
		allocated = udf_bitmap_prealloc_blocks(sb,
						       map->s_uspace.s_bitmap,
						       partition, first_block,
						       block_count);
	else if (map->s_partition_flags & UDF_PART_FLAG_UNALLOC_TABLE)
		allocated = udf_table_prealloc_blocks(sb,
						      map->s_uspace.s_table,
						      partition, first_block,
						      block_count);
	else if (map->s_partition_flags & UDF_PART_FLAG_FREED_BITMAP)
		allocated = udf_bitmap_prealloc_blocks(sb,
						       map->s_fspace.s_bitmap,
						       partition, first_block,
						       block_count);
	else if (map->s_partition_flags & UDF_PART_FLAG_FREED_TABLE)
		allocated = udf_table_prealloc_blocks(sb,
						      map->s_fspace.s_table,
						      partition, first_block,
						      block_count);
	else
		return 0;

	if (inode && allocated > 0)
		inode_add_bytes(inode, allocated << sb->s_blocksize_bits);
	return allocated;
}