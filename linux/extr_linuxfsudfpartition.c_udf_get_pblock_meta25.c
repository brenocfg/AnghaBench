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
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct udf_sb_info {struct udf_part_map* s_partmaps; } ;
struct udf_meta_data {int s_flags; struct inode* s_mirror_fe; int /*<<< orphan*/  s_phys_partition_ref; int /*<<< orphan*/  s_mirror_file_loc; scalar_t__ s_metadata_fe; } ;
struct TYPE_2__ {struct udf_meta_data s_metadata; } ;
struct udf_part_map {TYPE_1__ s_type_specific; } ;
struct super_block {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int MF_MIRROR_FE_LOADED ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  udf_debug (char*) ; 
 struct inode* udf_find_metadata_inode_efe (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int udf_try_read_meta (struct inode*,int,size_t,int) ; 
 int /*<<< orphan*/  udf_warn (struct super_block*,char*) ; 

uint32_t udf_get_pblock_meta25(struct super_block *sb, uint32_t block,
				uint16_t partition, uint32_t offset)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct udf_part_map *map;
	struct udf_meta_data *mdata;
	uint32_t retblk;
	struct inode *inode;

	udf_debug("READING from METADATA\n");

	map = &sbi->s_partmaps[partition];
	mdata = &map->s_type_specific.s_metadata;
	inode = mdata->s_metadata_fe ? : mdata->s_mirror_fe;

	if (!inode)
		return 0xFFFFFFFF;

	retblk = udf_try_read_meta(inode, block, partition, offset);
	if (retblk == 0xFFFFFFFF && mdata->s_metadata_fe) {
		udf_warn(sb, "error reading from METADATA, trying to read from MIRROR\n");
		if (!(mdata->s_flags & MF_MIRROR_FE_LOADED)) {
			mdata->s_mirror_fe = udf_find_metadata_inode_efe(sb,
				mdata->s_mirror_file_loc,
				mdata->s_phys_partition_ref);
			if (IS_ERR(mdata->s_mirror_fe))
				mdata->s_mirror_fe = NULL;
			mdata->s_flags |= MF_MIRROR_FE_LOADED;
		}

		inode = mdata->s_mirror_fe;
		if (!inode)
			return 0xFFFFFFFF;
		retblk = udf_try_read_meta(inode, block, partition, offset);
	}

	return retblk;
}