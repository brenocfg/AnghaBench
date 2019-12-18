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
struct inode {int /*<<< orphan*/  i_rwsem; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_ceph_flags; } ;

/* Variables and functions */
 int CEPH_I_ODIRECT ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_block_o_direct (struct ceph_inode_info*,struct inode*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  downgrade_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void
ceph_start_io_read(struct inode *inode)
{
	struct ceph_inode_info *ci = ceph_inode(inode);

	/* Be an optimist! */
	down_read(&inode->i_rwsem);
	if (!(READ_ONCE(ci->i_ceph_flags) & CEPH_I_ODIRECT))
		return;
	up_read(&inode->i_rwsem);
	/* Slow path.... */
	down_write(&inode->i_rwsem);
	ceph_block_o_direct(ci, inode);
	downgrade_write(&inode->i_rwsem);
}