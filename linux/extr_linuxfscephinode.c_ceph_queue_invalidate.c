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
struct inode {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_pg_inv_work; } ;
struct TYPE_3__ {int /*<<< orphan*/  pg_inv_wq; } ;

/* Variables and functions */
 TYPE_2__* ceph_inode (struct inode*) ; 
 TYPE_1__* ceph_inode_to_client (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ceph_queue_invalidate(struct inode *inode)
{
	ihold(inode);
	if (queue_work(ceph_inode_to_client(inode)->pg_inv_wq,
		       &ceph_inode(inode)->i_pg_inv_work)) {
		dout("ceph_queue_invalidate %p\n", inode);
	} else {
		dout("ceph_queue_invalidate %p failed\n", inode);
		iput(inode);
	}
}