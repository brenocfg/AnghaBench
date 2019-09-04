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
struct dentry {int /*<<< orphan*/  d_sb; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 int /*<<< orphan*/  EINVAL ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct dentry* __get_parent (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_snap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_vinop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *ceph_get_parent(struct dentry *child)
{
	/* don't re-export snaps */
	if (ceph_snap(d_inode(child)) != CEPH_NOSNAP)
		return ERR_PTR(-EINVAL);

	dout("get_parent %p ino %llx.%llx\n",
	     child, ceph_vinop(d_inode(child)));
	return __get_parent(child->d_sb, child, 0);
}