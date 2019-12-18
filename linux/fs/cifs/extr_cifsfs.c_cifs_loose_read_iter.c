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
struct kiocb {TYPE_1__* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int f_flags; } ;

/* Variables and functions */
 int O_DIRECT ; 
 scalar_t__ cifs_revalidate_mapping (struct inode*) ; 
 scalar_t__ cifs_user_readv (struct kiocb*,struct iov_iter*) ; 
 struct inode* file_inode (TYPE_1__*) ; 
 scalar_t__ generic_file_read_iter (struct kiocb*,struct iov_iter*) ; 

__attribute__((used)) static ssize_t
cifs_loose_read_iter(struct kiocb *iocb, struct iov_iter *iter)
{
	ssize_t rc;
	struct inode *inode = file_inode(iocb->ki_filp);

	if (iocb->ki_filp->f_flags & O_DIRECT)
		return cifs_user_readv(iocb, iter);

	rc = cifs_revalidate_mapping(inode);
	if (rc)
		return rc;

	return generic_file_read_iter(iocb, iter);
}