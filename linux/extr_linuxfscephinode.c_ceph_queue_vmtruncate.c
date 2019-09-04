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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_truncate_pending; int /*<<< orphan*/  i_vmtruncate_work; } ;
struct TYPE_2__ {int /*<<< orphan*/  trunc_wq; } ;

/* Variables and functions */
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 TYPE_1__* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,...) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ceph_queue_vmtruncate(struct inode *inode)
{
	struct ceph_inode_info *ci = ceph_inode(inode);

	ihold(inode);

	if (queue_work(ceph_sb_to_client(inode->i_sb)->trunc_wq,
		       &ci->i_vmtruncate_work)) {
		dout("ceph_queue_vmtruncate %p\n", inode);
	} else {
		dout("ceph_queue_vmtruncate %p failed, pending=%d\n",
		     inode, ci->i_truncate_pending);
		iput(inode);
	}
}