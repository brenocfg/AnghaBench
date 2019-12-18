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
struct inode {int /*<<< orphan*/  i_blocks; int /*<<< orphan*/  i_size; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_ceph_lock; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int __ceph_should_report_size (struct ceph_inode_info*) ; 
 int /*<<< orphan*/  calc_inode_blocks (int /*<<< orphan*/ ) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool ceph_inode_set_size(struct inode *inode, loff_t size)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	bool ret;

	spin_lock(&ci->i_ceph_lock);
	dout("set_size %p %llu -> %llu\n", inode, inode->i_size, size);
	i_size_write(inode, size);
	inode->i_blocks = calc_inode_blocks(size);

	ret = __ceph_should_report_size(ci);

	spin_unlock(&ci->i_ceph_lock);
	return ret;
}