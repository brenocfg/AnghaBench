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
struct iov_iter {int dummy; } ;
struct ffs_epfile {int /*<<< orphan*/  read_buffer; } ;
struct ffs_buffer {int length; int /*<<< orphan*/  storage; int /*<<< orphan*/  data; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ffs_buffer*) ; 
 int copy_to_iter (void*,int,struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  kfree (struct ffs_buffer*) ; 
 struct ffs_buffer* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t __ffs_epfile_read_data(struct ffs_epfile *epfile,
				      void *data, int data_len,
				      struct iov_iter *iter)
{
	struct ffs_buffer *buf;

	ssize_t ret = copy_to_iter(data, data_len, iter);
	if (likely(data_len == ret))
		return ret;

	if (unlikely(iov_iter_count(iter)))
		return -EFAULT;

	/* See ffs_copy_to_iter for more context. */
	pr_warn("functionfs read size %d > requested size %zd, splitting request into multiple reads.",
		data_len, ret);

	data_len -= ret;
	buf = kmalloc(sizeof(*buf) + data_len, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;
	buf->length = data_len;
	buf->data = buf->storage;
	memcpy(buf->storage, data + ret, data_len);

	/*
	 * At this point read_buffer is NULL or READ_BUFFER_DROP (if
	 * ffs_func_eps_disable has been called in the meanwhile).  See comment
	 * in struct ffs_epfile for full read_buffer pointer synchronisation
	 * story.
	 */
	if (unlikely(cmpxchg(&epfile->read_buffer, NULL, buf)))
		kfree(buf);

	return ret;
}