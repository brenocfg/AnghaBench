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
struct kiocb {TYPE_2__* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {TYPE_1__* f_mapping; } ;
struct TYPE_3__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_SWAPFILE (struct inode*) ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 scalar_t__ iov_iter_count (struct iov_iter*) ; 
 scalar_t__ iov_iter_rw (struct iov_iter*) ; 
 int /*<<< orphan*/  nfs_file_direct_read (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  nfs_file_direct_write (struct kiocb*,struct iov_iter*) ; 

ssize_t nfs_direct_IO(struct kiocb *iocb, struct iov_iter *iter)
{
	struct inode *inode = iocb->ki_filp->f_mapping->host;

	/* we only support swap file calling nfs_direct_IO */
	if (!IS_SWAPFILE(inode))
		return 0;

	VM_BUG_ON(iov_iter_count(iter) != PAGE_SIZE);

	if (iov_iter_rw(iter) == READ)
		return nfs_file_direct_read(iocb, iter);
	return nfs_file_direct_write(iocb, iter);
}