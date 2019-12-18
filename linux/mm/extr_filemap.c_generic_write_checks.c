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
struct kiocb {int ki_flags; int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int ssize_t ;
typedef  int loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETXTBSY ; 
 int IOCB_APPEND ; 
 int IOCB_DIRECT ; 
 int IOCB_NOWAIT ; 
 scalar_t__ IS_SWAPFILE (struct inode*) ; 
 int generic_write_check_limits (struct file*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_truncate (struct iov_iter*,int) ; 

inline ssize_t generic_write_checks(struct kiocb *iocb, struct iov_iter *from)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_mapping->host;
	loff_t count;
	int ret;

	if (IS_SWAPFILE(inode))
		return -ETXTBSY;

	if (!iov_iter_count(from))
		return 0;

	/* FIXME: this is for backwards compatibility with 2.4 */
	if (iocb->ki_flags & IOCB_APPEND)
		iocb->ki_pos = i_size_read(inode);

	if ((iocb->ki_flags & IOCB_NOWAIT) && !(iocb->ki_flags & IOCB_DIRECT))
		return -EINVAL;

	count = iov_iter_count(from);
	ret = generic_write_check_limits(file, iocb->ki_pos, &count);
	if (ret)
		return ret;

	iov_iter_truncate(from, count);
	return iov_iter_count(from);
}