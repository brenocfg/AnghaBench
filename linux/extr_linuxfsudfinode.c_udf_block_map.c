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
typedef  scalar_t__ udf_pblk_t ;
struct kernel_lb_addr {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct extent_position {int /*<<< orphan*/  bh; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_data_sem; } ;

/* Variables and functions */
 int EXT_RECORDED_ALLOCATED ; 
 int /*<<< orphan*/  UDF_FLAG_VARCONV ; 
 TYPE_1__* UDF_I (struct inode*) ; 
 scalar_t__ UDF_QUERY_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int inode_bmap (struct inode*,int /*<<< orphan*/ ,struct extent_position*,struct kernel_lb_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ udf_fixed_to_variable (scalar_t__) ; 
 scalar_t__ udf_get_lb_pblock (int /*<<< orphan*/ ,struct kernel_lb_addr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

udf_pblk_t udf_block_map(struct inode *inode, sector_t block)
{
	struct kernel_lb_addr eloc;
	uint32_t elen;
	sector_t offset;
	struct extent_position epos = {};
	udf_pblk_t ret;

	down_read(&UDF_I(inode)->i_data_sem);

	if (inode_bmap(inode, block, &epos, &eloc, &elen, &offset) ==
						(EXT_RECORDED_ALLOCATED >> 30))
		ret = udf_get_lb_pblock(inode->i_sb, &eloc, offset);
	else
		ret = 0;

	up_read(&UDF_I(inode)->i_data_sem);
	brelse(epos.bh);

	if (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_VARCONV))
		return udf_fixed_to_variable(ret);
	else
		return ret;
}