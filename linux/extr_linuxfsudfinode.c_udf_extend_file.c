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
typedef  int /*<<< orphan*/  uint32_t ;
struct udf_inode_info {scalar_t__ i_alloc_type; int i_lenExtents; } ;
struct super_block {int s_blocksize_bits; int s_blocksize; } ;
struct short_ad {int dummy; } ;
struct long_ad {int dummy; } ;
struct TYPE_2__ {scalar_t__ partitionReferenceNum; scalar_t__ logicalBlockNum; } ;
struct kernel_long_ad {int extLength; TYPE_1__ extLocation; } ;
struct kernel_lb_addr {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct extent_position {int offset; scalar_t__ bh; } ;
struct allocExtDesc {int dummy; } ;
typedef  scalar_t__ sector_t ;
typedef  int loff_t ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EXT_NOT_RECORDED_NOT_ALLOCATED ; 
 scalar_t__ ICBTAG_FLAG_AD_LONG ; 
 scalar_t__ ICBTAG_FLAG_AD_SHORT ; 
 struct udf_inode_info* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  brelse (scalar_t__) ; 
 int inode_bmap (struct inode*,scalar_t__,struct extent_position*,struct kernel_lb_addr*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int udf_do_extend_file (struct inode*,struct extent_position*,struct kernel_long_ad*,scalar_t__) ; 
 int udf_file_entry_alloc_offset (struct inode*) ; 
 int udf_next_aext (struct inode*,struct extent_position*,TYPE_1__*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int udf_extend_file(struct inode *inode, loff_t newsize)
{

	struct extent_position epos;
	struct kernel_lb_addr eloc;
	uint32_t elen;
	int8_t etype;
	struct super_block *sb = inode->i_sb;
	sector_t first_block = newsize >> sb->s_blocksize_bits, offset;
	int adsize;
	struct udf_inode_info *iinfo = UDF_I(inode);
	struct kernel_long_ad extent;
	int err;

	if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = sizeof(struct short_ad);
	else if (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = sizeof(struct long_ad);
	else
		BUG();

	etype = inode_bmap(inode, first_block, &epos, &eloc, &elen, &offset);

	/* File has extent covering the new size (could happen when extending
	 * inside a block)? */
	if (etype != -1)
		return 0;
	if (newsize & (sb->s_blocksize - 1))
		offset++;
	/* Extended file just to the boundary of the last file block? */
	if (offset == 0)
		return 0;

	/* Truncate is extending the file by 'offset' blocks */
	if ((!epos.bh && epos.offset == udf_file_entry_alloc_offset(inode)) ||
	    (epos.bh && epos.offset == sizeof(struct allocExtDesc))) {
		/* File has no extents at all or has empty last
		 * indirect extent! Create a fake extent... */
		extent.extLocation.logicalBlockNum = 0;
		extent.extLocation.partitionReferenceNum = 0;
		extent.extLength = EXT_NOT_RECORDED_NOT_ALLOCATED;
	} else {
		epos.offset -= adsize;
		etype = udf_next_aext(inode, &epos, &extent.extLocation,
				      &extent.extLength, 0);
		extent.extLength |= etype << 30;
	}
	err = udf_do_extend_file(inode, &epos, &extent, offset);
	if (err < 0)
		goto out;
	err = 0;
	iinfo->i_lenExtents = newsize;
out:
	brelse(epos.bh);
	return err;
}