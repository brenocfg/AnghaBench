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
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct fuse_io_priv {TYPE_1__* iocb; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  ki_filp; } ;

/* Variables and functions */
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_direct_io (struct fuse_io_priv*,struct iov_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_invalidate_atime (struct inode*) ; 

__attribute__((used)) static ssize_t __fuse_direct_read(struct fuse_io_priv *io,
				  struct iov_iter *iter,
				  loff_t *ppos)
{
	ssize_t res;
	struct inode *inode = file_inode(io->iocb->ki_filp);

	res = fuse_direct_io(io, iter, ppos, 0);

	fuse_invalidate_atime(inode);

	return res;
}