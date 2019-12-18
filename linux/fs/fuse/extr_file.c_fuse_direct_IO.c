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
struct kiocb {scalar_t__ ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct fuse_io_priv {int reqs; int bytes; int write; int async; int blocking; int /*<<< orphan*/  refcnt; int /*<<< orphan*/ * done; struct kiocb* iocb; scalar_t__ err; scalar_t__ offset; scalar_t__ size; int /*<<< orphan*/  lock; } ;
struct fuse_file {TYPE_2__* fc; } ;
struct file {TYPE_1__* f_mapping; struct fuse_file* private_data; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {int async_dio; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 scalar_t__ EIOCBQUEUED ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  FUSE_DIO_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ READ ; 
 scalar_t__ WRITE ; 
 scalar_t__ __fuse_direct_read (struct fuse_io_priv*,struct iov_iter*,scalar_t__*) ; 
 int /*<<< orphan*/  fuse_aio_complete (struct fuse_io_priv*,scalar_t__,int) ; 
 scalar_t__ fuse_direct_io (struct fuse_io_priv*,struct iov_iter*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_do_truncate (struct file*) ; 
 scalar_t__ fuse_get_res_by_io (struct fuse_io_priv*) ; 
 int /*<<< orphan*/  fuse_invalidate_attr (struct inode*) ; 
 int /*<<< orphan*/  fuse_io_release ; 
 int /*<<< orphan*/  fuse_round_up (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  fuse_write_update_size (struct inode*,scalar_t__) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 scalar_t__ iov_iter_rw (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_truncate (struct iov_iter*,int /*<<< orphan*/ ) ; 
 int is_sync_kiocb (struct kiocb*) ; 
 struct fuse_io_priv* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
fuse_direct_IO(struct kiocb *iocb, struct iov_iter *iter)
{
	DECLARE_COMPLETION_ONSTACK(wait);
	ssize_t ret = 0;
	struct file *file = iocb->ki_filp;
	struct fuse_file *ff = file->private_data;
	bool async_dio = ff->fc->async_dio;
	loff_t pos = 0;
	struct inode *inode;
	loff_t i_size;
	size_t count = iov_iter_count(iter);
	loff_t offset = iocb->ki_pos;
	struct fuse_io_priv *io;

	pos = offset;
	inode = file->f_mapping->host;
	i_size = i_size_read(inode);

	if ((iov_iter_rw(iter) == READ) && (offset > i_size))
		return 0;

	/* optimization for short read */
	if (async_dio && iov_iter_rw(iter) != WRITE && offset + count > i_size) {
		if (offset >= i_size)
			return 0;
		iov_iter_truncate(iter, fuse_round_up(ff->fc, i_size - offset));
		count = iov_iter_count(iter);
	}

	io = kmalloc(sizeof(struct fuse_io_priv), GFP_KERNEL);
	if (!io)
		return -ENOMEM;
	spin_lock_init(&io->lock);
	kref_init(&io->refcnt);
	io->reqs = 1;
	io->bytes = -1;
	io->size = 0;
	io->offset = offset;
	io->write = (iov_iter_rw(iter) == WRITE);
	io->err = 0;
	/*
	 * By default, we want to optimize all I/Os with async request
	 * submission to the client filesystem if supported.
	 */
	io->async = async_dio;
	io->iocb = iocb;
	io->blocking = is_sync_kiocb(iocb);

	/*
	 * We cannot asynchronously extend the size of a file.
	 * In such case the aio will behave exactly like sync io.
	 */
	if ((offset + count > i_size) && iov_iter_rw(iter) == WRITE)
		io->blocking = true;

	if (io->async && io->blocking) {
		/*
		 * Additional reference to keep io around after
		 * calling fuse_aio_complete()
		 */
		kref_get(&io->refcnt);
		io->done = &wait;
	}

	if (iov_iter_rw(iter) == WRITE) {
		ret = fuse_direct_io(io, iter, &pos, FUSE_DIO_WRITE);
		fuse_invalidate_attr(inode);
	} else {
		ret = __fuse_direct_read(io, iter, &pos);
	}

	if (io->async) {
		bool blocking = io->blocking;

		fuse_aio_complete(io, ret < 0 ? ret : 0, -1);

		/* we have a non-extending, async request, so return */
		if (!blocking)
			return -EIOCBQUEUED;

		wait_for_completion(&wait);
		ret = fuse_get_res_by_io(io);
	}

	kref_put(&io->refcnt, fuse_io_release);

	if (iov_iter_rw(iter) == WRITE) {
		if (ret > 0)
			fuse_write_update_size(inode, pos);
		else if (ret < 0 && offset + count > i_size)
			fuse_do_truncate(file);
	}

	return ret;
}