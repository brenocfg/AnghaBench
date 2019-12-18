#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  udf_pblk_t ;
struct super_block {scalar_t__ s_blocksize; } ;
struct short_ad {int dummy; } ;
struct long_ad {int dummy; } ;
struct kernel_lb_addr {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  logicalBlockNum; int /*<<< orphan*/  partitionReferenceNum; } ;
struct extent_position {scalar_t__ offset; TYPE_1__ block; } ;
struct TYPE_4__ {scalar_t__ i_alloc_type; } ;

/* Variables and functions */
 int EIO ; 
 int ENOSPC ; 
 scalar_t__ ICBTAG_FLAG_AD_LONG ; 
 scalar_t__ ICBTAG_FLAG_AD_SHORT ; 
 TYPE_2__* UDF_I (struct inode*) ; 
 int __udf_add_aext (struct inode*,struct extent_position*,struct kernel_lb_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udf_new_block (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int udf_setup_indirect_aext (struct inode*,int /*<<< orphan*/ ,struct extent_position*) ; 

int udf_add_aext(struct inode *inode, struct extent_position *epos,
		 struct kernel_lb_addr *eloc, uint32_t elen, int inc)
{
	int adsize;
	struct super_block *sb = inode->i_sb;

	if (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = sizeof(struct short_ad);
	else if (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = sizeof(struct long_ad);
	else
		return -EIO;

	if (epos->offset + (2 * adsize) > sb->s_blocksize) {
		int err;
		udf_pblk_t new_block;

		new_block = udf_new_block(sb, NULL,
					  epos->block.partitionReferenceNum,
					  epos->block.logicalBlockNum, &err);
		if (!new_block)
			return -ENOSPC;

		err = udf_setup_indirect_aext(inode, new_block, epos);
		if (err)
			return err;
	}

	return __udf_add_aext(inode, epos, eloc, elen, inc);
}