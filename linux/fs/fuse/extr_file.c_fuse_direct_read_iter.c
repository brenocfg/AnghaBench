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
struct kiocb {int ki_flags; int /*<<< orphan*/  ki_pos; } ;
struct iov_iter {int dummy; } ;
struct fuse_io_priv {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct fuse_io_priv FUSE_IO_PRIV_SYNC (struct kiocb*) ; 
 int IOCB_DIRECT ; 
 int /*<<< orphan*/  __fuse_direct_read (struct fuse_io_priv*,struct iov_iter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_direct_IO (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  is_sync_kiocb (struct kiocb*) ; 

__attribute__((used)) static ssize_t fuse_direct_read_iter(struct kiocb *iocb, struct iov_iter *to)
{
	ssize_t res;

	if (!is_sync_kiocb(iocb) && iocb->ki_flags & IOCB_DIRECT) {
		res = fuse_direct_IO(iocb, to);
	} else {
		struct fuse_io_priv io = FUSE_IO_PRIV_SYNC(iocb);

		res = __fuse_direct_read(&io, to, &iocb->ki_pos);
	}

	return res;
}