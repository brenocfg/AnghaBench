#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kiocb {int ki_flags; TYPE_1__* ki_filp; scalar_t__ ki_pos; } ;
struct iov_iter {int dummy; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 int IOCB_DIRECT ; 
 int /*<<< orphan*/  NFSIOS_NORMALREADBYTES ; 
 int /*<<< orphan*/  dprintk (char*,TYPE_1__*,int /*<<< orphan*/ ,unsigned long) ; 
 struct inode* file_inode (TYPE_1__*) ; 
 scalar_t__ generic_file_read_iter (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  nfs_add_stats (struct inode*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nfs_end_io_read (struct inode*) ; 
 scalar_t__ nfs_file_direct_read (struct kiocb*,struct iov_iter*) ; 
 scalar_t__ nfs_revalidate_mapping (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_start_io_read (struct inode*) ; 

ssize_t
nfs_file_read(struct kiocb *iocb, struct iov_iter *to)
{
	struct inode *inode = file_inode(iocb->ki_filp);
	ssize_t result;

	if (iocb->ki_flags & IOCB_DIRECT)
		return nfs_file_direct_read(iocb, to);

	dprintk("NFS: read(%pD2, %zu@%lu)\n",
		iocb->ki_filp,
		iov_iter_count(to), (unsigned long) iocb->ki_pos);

	nfs_start_io_read(inode);
	result = nfs_revalidate_mapping(inode, iocb->ki_filp->f_mapping);
	if (!result) {
		result = generic_file_read_iter(iocb, to);
		if (result > 0)
			nfs_add_stats(inode, NFSIOS_NORMALREADBYTES, result);
	}
	nfs_end_io_read(inode);
	return result;
}