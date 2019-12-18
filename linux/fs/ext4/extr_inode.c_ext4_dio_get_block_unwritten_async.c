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
struct buffer_head {int /*<<< orphan*/ * b_private; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  ext4_io_end_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EXT4_GET_BLOCKS_IO_CREATE_EXT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ buffer_unwritten (struct buffer_head*) ; 
 int ext4_get_block_trans (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ext4_init_io_end (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_journal_current_handle () ; 
 int /*<<< orphan*/  ext4_set_io_unwritten_flag (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_buffer_defer_completion (struct buffer_head*) ; 

__attribute__((used)) static int ext4_dio_get_block_unwritten_async(struct inode *inode,
		sector_t iblock, struct buffer_head *bh_result,	int create)
{
	int ret;

	/* We don't expect handle for direct IO */
	WARN_ON_ONCE(ext4_journal_current_handle());

	ret = ext4_get_block_trans(inode, iblock, bh_result,
				   EXT4_GET_BLOCKS_IO_CREATE_EXT);

	/*
	 * When doing DIO using unwritten extents, we need io_end to convert
	 * unwritten extents to written on IO completion. We allocate io_end
	 * once we spot unwritten extent and store it in b_private. Generic
	 * DIO code keeps b_private set and furthermore passes the value to
	 * our completion callback in 'private' argument.
	 */
	if (!ret && buffer_unwritten(bh_result)) {
		if (!bh_result->b_private) {
			ext4_io_end_t *io_end;

			io_end = ext4_init_io_end(inode, GFP_KERNEL);
			if (!io_end)
				return -ENOMEM;
			bh_result->b_private = io_end;
			ext4_set_io_unwritten_flag(inode, io_end);
		}
		set_buffer_defer_completion(bh_result);
	}

	return ret;
}