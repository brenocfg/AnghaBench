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
struct fuse_io_priv {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_DIO_CUSE ; 
 struct fuse_io_priv FUSE_IO_PRIV_SYNC (struct kiocb*) ; 
 int /*<<< orphan*/  fuse_direct_io (struct fuse_io_priv*,struct iov_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t cuse_read_iter(struct kiocb *kiocb, struct iov_iter *to)
{
	struct fuse_io_priv io = FUSE_IO_PRIV_SYNC(kiocb);
	loff_t pos = 0;

	return fuse_direct_io(&io, to, &pos, FUSE_DIO_CUSE);
}