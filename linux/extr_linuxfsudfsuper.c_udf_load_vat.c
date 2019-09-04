#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct virtualAllocationTable20 {int /*<<< orphan*/  lengthHeader; } ;
struct udf_sb_info {int s_last_block; TYPE_5__* s_vat_inode; struct udf_part_map* s_partmaps; } ;
struct TYPE_9__ {int s_start_offset; int s_num_entries; } ;
struct TYPE_10__ {TYPE_3__ s_virtual; } ;
struct udf_part_map {scalar_t__ s_partition_type; TYPE_4__ s_type_specific; } ;
struct TYPE_8__ {scalar_t__ i_data; } ;
struct udf_inode_info {scalar_t__ i_alloc_type; TYPE_2__ i_ext; } ;
struct super_block {int s_blocksize_bits; TYPE_1__* s_bdev; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int sector_t ;
struct TYPE_11__ {int i_size; } ;
struct TYPE_7__ {int /*<<< orphan*/  bd_inode; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ ICBTAG_FLAG_AD_IN_ICB ; 
 struct udf_inode_info* UDF_I (TYPE_5__*) ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 scalar_t__ UDF_VIRTUAL_MAP15 ; 
 scalar_t__ UDF_VIRTUAL_MAP20 ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_notice (char*,unsigned long,unsigned long) ; 
 struct buffer_head* sb_bread (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_block_map (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udf_find_vat_block (struct super_block*,int,int,int) ; 

__attribute__((used)) static int udf_load_vat(struct super_block *sb, int p_index, int type1_index)
{
	struct udf_sb_info *sbi = UDF_SB(sb);
	struct udf_part_map *map = &sbi->s_partmaps[p_index];
	struct buffer_head *bh = NULL;
	struct udf_inode_info *vati;
	uint32_t pos;
	struct virtualAllocationTable20 *vat20;
	sector_t blocks = i_size_read(sb->s_bdev->bd_inode) >>
			  sb->s_blocksize_bits;

	udf_find_vat_block(sb, p_index, type1_index, sbi->s_last_block);
	if (!sbi->s_vat_inode &&
	    sbi->s_last_block != blocks - 1) {
		pr_notice("Failed to read VAT inode from the last recorded block (%lu), retrying with the last block of the device (%lu).\n",
			  (unsigned long)sbi->s_last_block,
			  (unsigned long)blocks - 1);
		udf_find_vat_block(sb, p_index, type1_index, blocks - 1);
	}
	if (!sbi->s_vat_inode)
		return -EIO;

	if (map->s_partition_type == UDF_VIRTUAL_MAP15) {
		map->s_type_specific.s_virtual.s_start_offset = 0;
		map->s_type_specific.s_virtual.s_num_entries =
			(sbi->s_vat_inode->i_size - 36) >> 2;
	} else if (map->s_partition_type == UDF_VIRTUAL_MAP20) {
		vati = UDF_I(sbi->s_vat_inode);
		if (vati->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB) {
			pos = udf_block_map(sbi->s_vat_inode, 0);
			bh = sb_bread(sb, pos);
			if (!bh)
				return -EIO;
			vat20 = (struct virtualAllocationTable20 *)bh->b_data;
		} else {
			vat20 = (struct virtualAllocationTable20 *)
							vati->i_ext.i_data;
		}

		map->s_type_specific.s_virtual.s_start_offset =
			le16_to_cpu(vat20->lengthHeader);
		map->s_type_specific.s_virtual.s_num_entries =
			(sbi->s_vat_inode->i_size -
				map->s_type_specific.s_virtual.
					s_start_offset) >> 2;
		brelse(bh);
	}
	return 0;
}