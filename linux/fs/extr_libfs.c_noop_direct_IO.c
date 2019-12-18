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
 int /*<<< orphan*/  EINVAL ; 

ssize_t noop_direct_IO(struct kiocb *iocb, struct iov_iter *iter)
{
	/*
	 * iomap based filesystems support direct I/O without need for
	 * this callback. However, it still needs to be set in
	 * inode->a_ops so that open/fcntl know that direct I/O is
	 * generally supported.
	 */
	return -EINVAL;
}