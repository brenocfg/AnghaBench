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
struct kiocb {int dummy; } ;
struct iov_iter {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int BIO_MAX_PAGES ; 
 int /*<<< orphan*/  __blkdev_direct_IO (struct kiocb*,struct iov_iter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __blkdev_direct_IO_simple (struct kiocb*,struct iov_iter*,int) ; 
 int iov_iter_npages (struct iov_iter*,int) ; 
 scalar_t__ is_sync_kiocb (struct kiocb*) ; 
 int /*<<< orphan*/  min (int,int) ; 

__attribute__((used)) static ssize_t
blkdev_direct_IO(struct kiocb *iocb, struct iov_iter *iter)
{
	int nr_pages;

	nr_pages = iov_iter_npages(iter, BIO_MAX_PAGES + 1);
	if (!nr_pages)
		return 0;
	if (is_sync_kiocb(iocb) && nr_pages <= BIO_MAX_PAGES)
		return __blkdev_direct_IO_simple(iocb, iter, nr_pages);

	return __blkdev_direct_IO(iocb, iter, min(nr_pages, BIO_MAX_PAGES));
}