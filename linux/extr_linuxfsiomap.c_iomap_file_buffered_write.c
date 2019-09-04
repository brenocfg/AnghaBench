#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kiocb {scalar_t__ ki_pos; TYPE_2__* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct iomap_ops {int dummy; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {TYPE_1__* f_mapping; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMAP_WRITE ; 
 scalar_t__ iomap_apply (struct inode*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,struct iomap_ops const*,struct iov_iter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iomap_write_actor ; 
 scalar_t__ iov_iter_count (struct iov_iter*) ; 

ssize_t
iomap_file_buffered_write(struct kiocb *iocb, struct iov_iter *iter,
		const struct iomap_ops *ops)
{
	struct inode *inode = iocb->ki_filp->f_mapping->host;
	loff_t pos = iocb->ki_pos, ret = 0, written = 0;

	while (iov_iter_count(iter)) {
		ret = iomap_apply(inode, pos, iov_iter_count(iter),
				IOMAP_WRITE, ops, iter, iomap_write_actor);
		if (ret <= 0)
			break;
		pos += ret;
		written += ret;
	}

	return written ? written : ret;
}