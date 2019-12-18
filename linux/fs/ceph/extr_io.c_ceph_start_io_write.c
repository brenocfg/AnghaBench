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

/* Variables and functions */
 int /*<<< orphan*/  ceph_block_o_direct (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 

void
ceph_start_io_write(struct inode *inode)
{
	down_write(&inode->i_rwsem);
	ceph_block_o_direct(ceph_inode(inode), inode);
}