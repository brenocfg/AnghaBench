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
struct kiocb {int /*<<< orphan*/  ki_pos; TYPE_1__* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct ashmem_area {scalar_t__ size; TYPE_2__* file; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  f_pos; } ;
struct TYPE_3__ {struct ashmem_area* private_data; } ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  ashmem_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vfs_iter_read (TYPE_2__*,struct iov_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ashmem_read_iter(struct kiocb *iocb, struct iov_iter *iter)
{
	struct ashmem_area *asma = iocb->ki_filp->private_data;
	int ret = 0;

	mutex_lock(&ashmem_mutex);

	/* If size is not set, or set to 0, always return EOF. */
	if (asma->size == 0)
		goto out_unlock;

	if (!asma->file) {
		ret = -EBADF;
		goto out_unlock;
	}

	/*
	 * asma and asma->file are used outside the lock here.  We assume
	 * once asma->file is set it will never be changed, and will not
	 * be destroyed until all references to the file are dropped and
	 * ashmem_release is called.
	 */
	mutex_unlock(&ashmem_mutex);
	ret = vfs_iter_read(asma->file, iter, &iocb->ki_pos, 0);
	mutex_lock(&ashmem_mutex);
	if (ret > 0)
		asma->file->f_pos = iocb->ki_pos;
out_unlock:
	mutex_unlock(&ashmem_mutex);
	return ret;
}