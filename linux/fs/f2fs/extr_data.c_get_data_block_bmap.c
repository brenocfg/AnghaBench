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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_2__ {scalar_t__ max_file_blocks; } ;

/* Variables and functions */
 int EFBIG ; 
 int /*<<< orphan*/  F2FS_GET_BLOCK_BMAP ; 
 TYPE_1__* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  NO_CHECK_TYPE ; 
 int __get_data_block (struct inode*,scalar_t__,struct buffer_head*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int get_data_block_bmap(struct inode *inode, sector_t iblock,
			struct buffer_head *bh_result, int create)
{
	/* Block number less than F2FS MAX BLOCKS */
	if (unlikely(iblock >= F2FS_I_SB(inode)->max_file_blocks))
		return -EFBIG;

	return __get_data_block(inode, iblock, bh_result, create,
						F2FS_GET_BLOCK_BMAP, NULL,
						NO_CHECK_TYPE, create);
}