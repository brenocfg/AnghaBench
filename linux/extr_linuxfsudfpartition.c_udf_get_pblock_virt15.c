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
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct udf_virtual_data {int s_num_entries; int s_start_offset; } ;
struct udf_sb_info {int /*<<< orphan*/  s_vat_inode; struct udf_part_map* s_partmaps; } ;
struct TYPE_4__ {struct udf_virtual_data s_virtual; } ;
struct udf_part_map {TYPE_1__ s_type_specific; } ;
struct TYPE_6__ {size_t partitionReferenceNum; } ;
struct TYPE_5__ {scalar_t__ i_data; } ;
struct udf_inode_info {scalar_t__ i_alloc_type; TYPE_3__ i_location; TYPE_2__ i_ext; } ;
struct super_block {int s_blocksize; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 struct udf_inode_info* UDF_I (int /*<<< orphan*/ ) ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_bread (struct super_block*,int) ; 
 int udf_block_map (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udf_debug (char*,...) ; 
 int udf_get_pblock (struct super_block*,int,size_t,int) ; 

uint32_t udf_get_pblock_virt15(struct super_block *sb, uint32_t block,
			       uint16_t partition, uint32_t offset)
{
	struct buffer_head *bh = NULL;
	uint32_t newblock;
	uint32_t index;
	uint32_t loc;
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct udf_part_map *map;
	struct udf_virtual_data *vdata;
	struct udf_inode_info *iinfo = UDF_I(sbi->s_vat_inode);

	map = &sbi->s_partmaps[partition];
	vdata = &map->s_type_specific.s_virtual;

	if (block > vdata->s_num_entries) {
		udf_debug("Trying to access block beyond end of VAT (%u max %u)\n",
			  block, vdata->s_num_entries);
		return 0xFFFFFFFF;
	}

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) {
		loc = le32_to_cpu(((__le32 *)(iinfo->i_ext.i_data +
			vdata->s_start_offset))[block]);
		goto translate;
	}
	index = (sb->s_blocksize - vdata->s_start_offset) / sizeof(uint32_t);
	if (block >= index) {
		block -= index;
		newblock = 1 + (block / (sb->s_blocksize / sizeof(uint32_t)));
		index = block % (sb->s_blocksize / sizeof(uint32_t));
	} else {
		newblock = 0;
		index = vdata->s_start_offset / sizeof(uint32_t) + block;
	}

	loc = udf_block_map(sbi->s_vat_inode, newblock);

	bh = sb_bread(sb, loc);
	if (!bh) {
		udf_debug("get_pblock(UDF_VIRTUAL_MAP:%p,%u,%u) VAT: %u[%u]\n",
			  sb, block, partition, loc, index);
		return 0xFFFFFFFF;
	}

	loc = le32_to_cpu(((__le32 *)bh->b_data)[index]);

	brelse(bh);

translate:
	if (iinfo->i_location.partitionReferenceNum == partition) {
		udf_debug("recursive call to udf_get_pblock!\n");
		return 0xFFFFFFFF;
	}

	return udf_get_pblock(sb, loc,
			      iinfo->i_location.partitionReferenceNum,
			      offset);
}