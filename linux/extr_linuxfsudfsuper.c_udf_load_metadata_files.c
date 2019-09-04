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
struct udf_sb_info {struct udf_part_map* s_partmaps; } ;
struct udf_meta_data {int s_phys_partition_ref; int s_bitmap_file_loc; struct inode* s_bitmap_fe; struct inode* s_metadata_fe; struct inode* s_mirror_fe; int /*<<< orphan*/  s_mirror_file_loc; int /*<<< orphan*/  s_meta_file_loc; } ;
struct TYPE_2__ {struct udf_meta_data s_metadata; } ;
struct udf_part_map {TYPE_1__ s_type_specific; } ;
struct super_block {int dummy; } ;
struct kernel_lb_addr {int logicalBlockNum; int partitionReferenceNum; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  udf_debug (char*,...) ; 
 int /*<<< orphan*/  udf_err (struct super_block*,char*) ; 
 struct inode* udf_find_metadata_inode_efe (struct super_block*,int /*<<< orphan*/ ,int) ; 
 struct inode* udf_iget_special (struct super_block*,struct kernel_lb_addr*) ; 
 int /*<<< orphan*/  udf_warn (struct super_block*,char*) ; 

__attribute__((used)) static int udf_load_metadata_files(struct super_block *sb, int partition,
				   int type1_index)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct udf_part_map *map;
	struct udf_meta_data *mdata;
	struct kernel_lb_addr addr;
	struct inode *fe;

	map = &sbi->s_partmaps[partition];
	mdata = &map->s_type_specific.s_metadata;
	mdata->s_phys_partition_ref = type1_index;

	/* metadata address */
	udf_debug("Metadata file location: block = %u part = %u\n",
		  mdata->s_meta_file_loc, mdata->s_phys_partition_ref);

	fe = udf_find_metadata_inode_efe(sb, mdata->s_meta_file_loc,
					 mdata->s_phys_partition_ref);
	if (IS_ERR(fe)) {
		/* mirror file entry */
		udf_debug("Mirror metadata file location: block = %u part = %u\n",
			  mdata->s_mirror_file_loc, mdata->s_phys_partition_ref);

		fe = udf_find_metadata_inode_efe(sb, mdata->s_mirror_file_loc,
						 mdata->s_phys_partition_ref);

		if (IS_ERR(fe)) {
			udf_err(sb, "Both metadata and mirror metadata inode efe can not found\n");
			return PTR_ERR(fe);
		}
		mdata->s_mirror_fe = fe;
	} else
		mdata->s_metadata_fe = fe;


	/*
	 * bitmap file entry
	 * Note:
	 * Load only if bitmap file location differs from 0xFFFFFFFF (DCN-5102)
	*/
	if (mdata->s_bitmap_file_loc != 0xFFFFFFFF) {
		addr.logicalBlockNum = mdata->s_bitmap_file_loc;
		addr.partitionReferenceNum = mdata->s_phys_partition_ref;

		udf_debug("Bitmap file location: block = %u part = %u\n",
			  addr.logicalBlockNum, addr.partitionReferenceNum);

		fe = udf_iget_special(sb, &addr);
		if (IS_ERR(fe)) {
			if (sb_rdonly(sb))
				udf_warn(sb, "bitmap inode efe not found but it's ok since the disc is mounted read-only\n");
			else {
				udf_err(sb, "bitmap inode efe not found and attempted read-write mount\n");
				return PTR_ERR(fe);
			}
		} else
			mdata->s_bitmap_fe = fe;
	}

	udf_debug("udf_load_metadata_files Ok\n");
	return 0;
}