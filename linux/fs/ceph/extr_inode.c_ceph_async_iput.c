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
struct inode {int /*<<< orphan*/  i_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_work; } ;
struct TYPE_3__ {int /*<<< orphan*/  inode_wq; } ;

/* Variables and functions */
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 TYPE_2__* ceph_inode (struct inode*) ; 
 TYPE_1__* ceph_inode_to_client (struct inode*) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ceph_async_iput(struct inode *inode)
{
	if (!inode)
		return;
	for (;;) {
		if (atomic_add_unless(&inode->i_count, -1, 1))
			break;
		if (queue_work(ceph_inode_to_client(inode)->inode_wq,
			       &ceph_inode(inode)->i_work))
			break;
		/* queue work failed, i_count must be at least 2 */
	}
}