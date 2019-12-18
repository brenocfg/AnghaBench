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
typedef  scalar_t__ uint32_t ;
struct super_block {int s_blocksize; } ;
struct kernel_long_ad {int extLength; int /*<<< orphan*/  extLocation; } ;
struct inode {struct super_block* i_sb; } ;
struct extent_position {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_lenExtents; } ;

/* Variables and functions */
 TYPE_1__* UDF_I (struct inode*) ; 
 int /*<<< orphan*/  udf_write_aext (struct inode*,struct extent_position*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void udf_do_extend_final_block(struct inode *inode,
				      struct extent_position *last_pos,
				      struct kernel_long_ad *last_ext,
				      uint32_t final_block_len)
{
	struct super_block *sb = inode->i_sb;
	uint32_t added_bytes;

	added_bytes = final_block_len -
		      (last_ext->extLength & (sb->s_blocksize - 1));
	last_ext->extLength += added_bytes;
	UDF_I(inode)->i_lenExtents += added_bytes;

	udf_write_aext(inode, last_pos, &last_ext->extLocation,
			last_ext->extLength, 1);
}