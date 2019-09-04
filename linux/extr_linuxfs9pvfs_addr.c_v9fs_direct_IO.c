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
struct kiocb {scalar_t__ ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
struct file {int /*<<< orphan*/  private_data; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ WRITE ; 
 struct inode* file_inode (struct file*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_add_bytes (struct inode*,scalar_t__) ; 
 scalar_t__ iov_iter_rw (struct iov_iter*) ; 
 scalar_t__ p9_client_read (int /*<<< orphan*/ ,scalar_t__,struct iov_iter*,int*) ; 
 scalar_t__ p9_client_write (int /*<<< orphan*/ ,scalar_t__,struct iov_iter*,int*) ; 

__attribute__((used)) static ssize_t
v9fs_direct_IO(struct kiocb *iocb, struct iov_iter *iter)
{
	struct file *file = iocb->ki_filp;
	loff_t pos = iocb->ki_pos;
	ssize_t n;
	int err = 0;
	if (iov_iter_rw(iter) == WRITE) {
		n = p9_client_write(file->private_data, pos, iter, &err);
		if (n) {
			struct inode *inode = file_inode(file);
			loff_t i_size = i_size_read(inode);
			if (pos + n > i_size)
				inode_add_bytes(inode, pos + n - i_size);
		}
	} else {
		n = p9_client_read(file->private_data, pos, iter, &err);
	}
	return n ? n : err;
}