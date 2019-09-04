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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int _ext4_get_block (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 scalar_t__ buffer_unwritten (struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_debug (char*,int /*<<< orphan*/ ,int) ; 
 int ext4_journal_current_handle () ; 

__attribute__((used)) static int ext4_dio_get_block_overwrite(struct inode *inode, sector_t iblock,
		   struct buffer_head *bh_result, int create)
{
	int ret;

	ext4_debug("ext4_dio_get_block_overwrite: inode %lu, create flag %d\n",
		   inode->i_ino, create);
	/* We don't expect handle for direct IO */
	WARN_ON_ONCE(ext4_journal_current_handle());

	ret = _ext4_get_block(inode, iblock, bh_result, 0);
	/*
	 * Blocks should have been preallocated! ext4_file_write_iter() checks
	 * that.
	 */
	WARN_ON_ONCE(!buffer_mapped(bh_result) || buffer_unwritten(bh_result));

	return ret;
}