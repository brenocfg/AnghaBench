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
struct inode {int dummy; } ;
struct fuse_io_priv {int err; scalar_t__ bytes; int reqs; int /*<<< orphan*/  refcnt; TYPE_1__* iocb; scalar_t__ blocking; int /*<<< orphan*/  lock; int /*<<< orphan*/  done; } ;
struct fuse_inode {int /*<<< orphan*/  lock; int /*<<< orphan*/  attr_version; } ;
struct fuse_conn {int /*<<< orphan*/  attr_version; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* ki_complete ) (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ki_filp; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ fuse_get_res_by_io (struct fuse_io_priv*) ; 
 int /*<<< orphan*/  fuse_io_release ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fuse_aio_complete(struct fuse_io_priv *io, int err, ssize_t pos)
{
	int left;

	spin_lock(&io->lock);
	if (err)
		io->err = io->err ? : err;
	else if (pos >= 0 && (io->bytes < 0 || pos < io->bytes))
		io->bytes = pos;

	left = --io->reqs;
	if (!left && io->blocking)
		complete(io->done);
	spin_unlock(&io->lock);

	if (!left && !io->blocking) {
		ssize_t res = fuse_get_res_by_io(io);

		if (res >= 0) {
			struct inode *inode = file_inode(io->iocb->ki_filp);
			struct fuse_conn *fc = get_fuse_conn(inode);
			struct fuse_inode *fi = get_fuse_inode(inode);

			spin_lock(&fi->lock);
			fi->attr_version = atomic64_inc_return(&fc->attr_version);
			spin_unlock(&fi->lock);
		}

		io->iocb->ki_complete(io->iocb, res, 0);
	}

	kref_put(&io->refcnt, fuse_io_release);
}