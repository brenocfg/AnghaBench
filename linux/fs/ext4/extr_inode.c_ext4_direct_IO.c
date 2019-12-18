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
struct kiocb {int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ IS_ENCRYPTED (struct inode*) ; 
 scalar_t__ READ ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_direct_IO_read (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  ext4_direct_IO_write (struct kiocb*,struct iov_iter*) ; 
 scalar_t__ ext4_has_inline_data (struct inode*) ; 
 scalar_t__ ext4_should_journal_data (struct inode*) ; 
 scalar_t__ fsverity_active (struct inode*) ; 
 size_t iov_iter_count (struct iov_iter*) ; 
 scalar_t__ iov_iter_rw (struct iov_iter*) ; 
 int /*<<< orphan*/  trace_ext4_direct_IO_enter (struct inode*,int /*<<< orphan*/ ,size_t,scalar_t__) ; 
 int /*<<< orphan*/  trace_ext4_direct_IO_exit (struct inode*,int /*<<< orphan*/ ,size_t,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ext4_direct_IO(struct kiocb *iocb, struct iov_iter *iter)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_mapping->host;
	size_t count = iov_iter_count(iter);
	loff_t offset = iocb->ki_pos;
	ssize_t ret;

#ifdef CONFIG_FS_ENCRYPTION
	if (IS_ENCRYPTED(inode) && S_ISREG(inode->i_mode))
		return 0;
#endif
	if (fsverity_active(inode))
		return 0;

	/*
	 * If we are doing data journalling we don't support O_DIRECT
	 */
	if (ext4_should_journal_data(inode))
		return 0;

	/* Let buffer I/O handle the inline data case. */
	if (ext4_has_inline_data(inode))
		return 0;

	trace_ext4_direct_IO_enter(inode, offset, count, iov_iter_rw(iter));
	if (iov_iter_rw(iter) == READ)
		ret = ext4_direct_IO_read(iocb, iter);
	else
		ret = ext4_direct_IO_write(iocb, iter);
	trace_ext4_direct_IO_exit(inode, offset, count, iov_iter_rw(iter), ret);
	return ret;
}