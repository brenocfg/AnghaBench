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
struct inode {int dummy; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_work_mask; int /*<<< orphan*/  i_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  inode_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_I_WORK_WRITEBACK ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 TYPE_1__* ceph_inode_to_client (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,...) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ceph_queue_writeback(struct inode *inode)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	set_bit(CEPH_I_WORK_WRITEBACK, &ci->i_work_mask);

	ihold(inode);
	if (queue_work(ceph_inode_to_client(inode)->inode_wq,
		       &ci->i_work)) {
		dout("ceph_queue_writeback %p\n", inode);
	} else {
		dout("ceph_queue_writeback %p already queued, mask=%lx\n",
		     inode, ci->i_work_mask);
		iput(inode);
	}
}