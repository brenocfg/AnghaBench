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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_GET_BLOCKS_CREATE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int _ext4_get_block (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ext4_get_block_trans (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_journal_current_handle () ; 

int ext4_dio_get_block(struct inode *inode, sector_t iblock,
		       struct buffer_head *bh, int create)
{
	/* We don't expect handle for direct IO */
	WARN_ON_ONCE(ext4_journal_current_handle());

	if (!create)
		return _ext4_get_block(inode, iblock, bh, 0);
	return ext4_get_block_trans(inode, iblock, bh, EXT4_GET_BLOCKS_CREATE);
}