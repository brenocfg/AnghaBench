#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct kiocb {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_7__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; TYPE_1__* inode; } ;
typedef  TYPE_2__ ext4_io_end_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_clear_io_unwritten_flag (TYPE_2__*) ; 
 int /*<<< orphan*/  ext4_put_io_end (TYPE_2__*) ; 
 int /*<<< orphan*/  ext_debug (char*,TYPE_2__*,int /*<<< orphan*/ ,struct kiocb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_end_io_dio(struct kiocb *iocb, loff_t offset,
			    ssize_t size, void *private)
{
        ext4_io_end_t *io_end = private;

	/* if not async direct IO just return */
	if (!io_end)
		return 0;

	ext_debug("ext4_end_io_dio(): io_end 0x%p "
		  "for inode %lu, iocb 0x%p, offset %llu, size %zd\n",
		  io_end, io_end->inode->i_ino, iocb, offset, size);

	/*
	 * Error during AIO DIO. We cannot convert unwritten extents as the
	 * data was not written. Just clear the unwritten flag and drop io_end.
	 */
	if (size <= 0) {
		ext4_clear_io_unwritten_flag(io_end);
		size = 0;
	}
	io_end->offset = offset;
	io_end->size = size;
	ext4_put_io_end(io_end);

	return 0;
}