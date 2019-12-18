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
struct udf_sb_info {struct udf_part_map* s_partmaps; } ;
struct TYPE_5__ {struct udf_bitmap* s_bitmap; struct inode* s_table; } ;
struct udf_part_map {int /*<<< orphan*/  s_partition_flags; TYPE_2__ s_uspace; void* s_partition_len; void* s_partition_root; int /*<<< orphan*/  s_partition_type; } ;
struct udf_bitmap {void* s_extPosition; } ;
struct super_block {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  extPosition; scalar_t__ extLength; } ;
struct TYPE_4__ {int /*<<< orphan*/  extPosition; scalar_t__ extLength; } ;
struct partitionHeaderDesc {TYPE_3__ unallocSpaceBitmap; TYPE_1__ unallocSpaceTable; } ;
struct partitionDesc {scalar_t__ accessType; scalar_t__ partitionContentsUse; int /*<<< orphan*/  partitionStartingLocation; int /*<<< orphan*/  partitionLength; } ;
struct kernel_lb_addr {void* logicalBlockNum; int partitionReferenceNum; } ;
struct inode {void* i_ino; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  PD_ACCESS_TYPE_OVERWRITABLE ; 
 int /*<<< orphan*/  PD_ACCESS_TYPE_READ_ONLY ; 
 int /*<<< orphan*/  PD_ACCESS_TYPE_REWRITABLE ; 
 int /*<<< orphan*/  PD_ACCESS_TYPE_WRITE_ONCE ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  UDF_FLAG_RW_INCOMPAT ; 
 int /*<<< orphan*/  UDF_PART_FLAG_OVERWRITABLE ; 
 int /*<<< orphan*/  UDF_PART_FLAG_READ_ONLY ; 
 int /*<<< orphan*/  UDF_PART_FLAG_REWRITABLE ; 
 int /*<<< orphan*/  UDF_PART_FLAG_UNALLOC_BITMAP ; 
 int /*<<< orphan*/  UDF_PART_FLAG_UNALLOC_TABLE ; 
 int /*<<< orphan*/  UDF_PART_FLAG_WRITE_ONCE ; 
 scalar_t__ UDF_QUERY_FLAG (struct super_block*,int /*<<< orphan*/ ) ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int check_partition_desc (struct super_block*,struct partitionDesc*,struct udf_part_map*) ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_debug (char*,int,...) ; 
 struct inode* udf_iget_special (struct super_block*,struct kernel_lb_addr*) ; 
 struct udf_bitmap* udf_sb_alloc_bitmap (struct super_block*,int) ; 

__attribute__((used)) static int udf_fill_partdesc_info(struct super_block *sb,
		struct partitionDesc *p, int p_index)
{
	struct udf_part_map *map;
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct partitionHeaderDesc *phd;
	int err;

	map = &sbi->s_partmaps[p_index];

	map->s_partition_len = le32_to_cpu(p->partitionLength); /* blocks */
	map->s_partition_root = le32_to_cpu(p->partitionStartingLocation);

	if (p->accessType == cpu_to_le32(PD_ACCESS_TYPE_READ_ONLY))
		map->s_partition_flags |= UDF_PART_FLAG_READ_ONLY;
	if (p->accessType == cpu_to_le32(PD_ACCESS_TYPE_WRITE_ONCE))
		map->s_partition_flags |= UDF_PART_FLAG_WRITE_ONCE;
	if (p->accessType == cpu_to_le32(PD_ACCESS_TYPE_REWRITABLE))
		map->s_partition_flags |= UDF_PART_FLAG_REWRITABLE;
	if (p->accessType == cpu_to_le32(PD_ACCESS_TYPE_OVERWRITABLE))
		map->s_partition_flags |= UDF_PART_FLAG_OVERWRITABLE;

	udf_debug("Partition (%d type %x) starts at physical %u, block length %u\n",
		  p_index, map->s_partition_type,
		  map->s_partition_root, map->s_partition_len);

	err = check_partition_desc(sb, p, map);
	if (err)
		return err;

	/*
	 * Skip loading allocation info it we cannot ever write to the fs.
	 * This is a correctness thing as we may have decided to force ro mount
	 * to avoid allocation info we don't support.
	 */
	if (UDF_QUERY_FLAG(sb, UDF_FLAG_RW_INCOMPAT))
		return 0;

	phd = (struct partitionHeaderDesc *)p->partitionContentsUse;
	if (phd->unallocSpaceTable.extLength) {
		struct kernel_lb_addr loc = {
			.logicalBlockNum = le32_to_cpu(
				phd->unallocSpaceTable.extPosition),
			.partitionReferenceNum = p_index,
		};
		struct inode *inode;

		inode = udf_iget_special(sb, &loc);
		if (IS_ERR(inode)) {
			udf_debug("cannot load unallocSpaceTable (part %d)\n",
				  p_index);
			return PTR_ERR(inode);
		}
		map->s_uspace.s_table = inode;
		map->s_partition_flags |= UDF_PART_FLAG_UNALLOC_TABLE;
		udf_debug("unallocSpaceTable (part %d) @ %lu\n",
			  p_index, map->s_uspace.s_table->i_ino);
	}

	if (phd->unallocSpaceBitmap.extLength) {
		struct udf_bitmap *bitmap = udf_sb_alloc_bitmap(sb, p_index);
		if (!bitmap)
			return -ENOMEM;
		map->s_uspace.s_bitmap = bitmap;
		bitmap->s_extPosition = le32_to_cpu(
				phd->unallocSpaceBitmap.extPosition);
		map->s_partition_flags |= UDF_PART_FLAG_UNALLOC_BITMAP;
		udf_debug("unallocSpaceBitmap (part %d) @ %u\n",
			  p_index, bitmap->s_extPosition);
	}

	return 0;
}