#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct inode {int /*<<< orphan*/  i_write_hint; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_GET_BLOCK_DIO ; 
 int __get_data_block (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_rw_hint_to_seg_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_data_block_dio(struct inode *inode, sector_t iblock,
			struct buffer_head *bh_result, int create)
{
	return __get_data_block(inode, iblock, bh_result, create,
				F2FS_GET_BLOCK_DIO, NULL,
				f2fs_rw_hint_to_seg_type(inode->i_write_hint),
				false);
}