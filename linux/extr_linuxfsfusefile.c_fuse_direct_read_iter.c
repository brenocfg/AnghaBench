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
struct kiocb {int /*<<< orphan*/  ki_pos; } ;
struct iov_iter {int dummy; } ;
struct fuse_io_priv {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct fuse_io_priv FUSE_IO_PRIV_SYNC (struct kiocb*) ; 
 int /*<<< orphan*/  __fuse_direct_read (struct fuse_io_priv*,struct iov_iter*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t fuse_direct_read_iter(struct kiocb *iocb, struct iov_iter *to)
{
	struct fuse_io_priv io = FUSE_IO_PRIV_SYNC(iocb);
	return __fuse_direct_read(&io, to, &iocb->ki_pos);
}