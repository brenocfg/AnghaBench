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
struct kiocb {int dummy; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct block_device {char* bd_queue; TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  get_block_t ;
typedef  int /*<<< orphan*/  dio_submit_t ;
typedef  int /*<<< orphan*/  dio_iodone_t ;
struct TYPE_2__ {char part_tbl; } ;

/* Variables and functions */
 int SMP_CACHE_BYTES ; 
 int /*<<< orphan*/  do_blockdev_direct_IO (struct kiocb*,struct inode*,struct block_device*,struct iov_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prefetch (char*) ; 

ssize_t __blockdev_direct_IO(struct kiocb *iocb, struct inode *inode,
			     struct block_device *bdev, struct iov_iter *iter,
			     get_block_t get_block,
			     dio_iodone_t end_io, dio_submit_t submit_io,
			     int flags)
{
	/*
	 * The block device state is needed in the end to finally
	 * submit everything.  Since it's likely to be cache cold
	 * prefetch it here as first thing to hide some of the
	 * latency.
	 *
	 * Attempt to prefetch the pieces we likely need later.
	 */
	prefetch(&bdev->bd_disk->part_tbl);
	prefetch(bdev->bd_queue);
	prefetch((char *)bdev->bd_queue + SMP_CACHE_BYTES);

	return do_blockdev_direct_IO(iocb, inode, bdev, iter, get_block,
				     end_io, submit_io, flags);
}