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
struct kiocb {int ki_flags; unsigned long ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {TYPE_2__* i_sb; } ;
struct file {int f_flags; TYPE_1__* f_mapping; } ;
typedef  unsigned long ssize_t ;
typedef  unsigned long loff_t ;
struct TYPE_4__ {unsigned long s_maxbytes; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 unsigned long EFBIG ; 
 unsigned long EINVAL ; 
 int IOCB_APPEND ; 
 int IOCB_DIRECT ; 
 int IOCB_NOWAIT ; 
 unsigned long MAX_NON_LFS ; 
 int O_LARGEFILE ; 
 int /*<<< orphan*/  RLIMIT_FSIZE ; 
 unsigned long RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGXFSZ ; 
 int /*<<< orphan*/  current ; 
 unsigned long i_size_read (struct inode*) ; 
 unsigned long iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_truncate (struct iov_iter*,unsigned long) ; 
 unsigned long rlimit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

inline ssize_t generic_write_checks(struct kiocb *iocb, struct iov_iter *from)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_mapping->host;
	unsigned long limit = rlimit(RLIMIT_FSIZE);
	loff_t pos;

	if (!iov_iter_count(from))
		return 0;

	/* FIXME: this is for backwards compatibility with 2.4 */
	if (iocb->ki_flags & IOCB_APPEND)
		iocb->ki_pos = i_size_read(inode);

	pos = iocb->ki_pos;

	if ((iocb->ki_flags & IOCB_NOWAIT) && !(iocb->ki_flags & IOCB_DIRECT))
		return -EINVAL;

	if (limit != RLIM_INFINITY) {
		if (iocb->ki_pos >= limit) {
			send_sig(SIGXFSZ, current, 0);
			return -EFBIG;
		}
		iov_iter_truncate(from, limit - (unsigned long)pos);
	}

	/*
	 * LFS rule
	 */
	if (unlikely(pos + iov_iter_count(from) > MAX_NON_LFS &&
				!(file->f_flags & O_LARGEFILE))) {
		if (pos >= MAX_NON_LFS)
			return -EFBIG;
		iov_iter_truncate(from, MAX_NON_LFS - (unsigned long)pos);
	}

	/*
	 * Are we about to exceed the fs block limit ?
	 *
	 * If we have written data it becomes a short write.  If we have
	 * exceeded without writing data we send a signal and return EFBIG.
	 * Linus frestrict idea will clean these up nicely..
	 */
	if (unlikely(pos >= inode->i_sb->s_maxbytes))
		return -EFBIG;

	iov_iter_truncate(from, inode->i_sb->s_maxbytes - pos);
	return iov_iter_count(from);
}