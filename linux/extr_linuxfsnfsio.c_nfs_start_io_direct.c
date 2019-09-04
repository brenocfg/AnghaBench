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
struct nfs_inode {int /*<<< orphan*/  flags; } ;
struct inode {int /*<<< orphan*/  i_rwsem; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_ODIRECT ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  downgrade_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_block_buffered (struct nfs_inode*,struct inode*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void
nfs_start_io_direct(struct inode *inode)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	/* Be an optimist! */
	down_read(&inode->i_rwsem);
	if (test_bit(NFS_INO_ODIRECT, &nfsi->flags) != 0)
		return;
	up_read(&inode->i_rwsem);
	/* Slow path.... */
	down_write(&inode->i_rwsem);
	nfs_block_buffered(nfsi, inode);
	downgrade_write(&inode->i_rwsem);
}