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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_shared_gen; int /*<<< orphan*/  i_ceph_lock; } ;
struct ceph_dentry_info {scalar_t__ lease_shared_gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_CAP_FILE_SHARED ; 
 int __ceph_caps_issued_mask (struct ceph_inode_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct ceph_dentry_info* ceph_dentry (struct dentry*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,unsigned int,struct dentry*,unsigned int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dir_lease_is_valid(struct inode *dir, struct dentry *dentry)
{
	struct ceph_inode_info *ci = ceph_inode(dir);
	struct ceph_dentry_info *di = ceph_dentry(dentry);
	int valid = 0;

	spin_lock(&ci->i_ceph_lock);
	if (atomic_read(&ci->i_shared_gen) == di->lease_shared_gen)
		valid = __ceph_caps_issued_mask(ci, CEPH_CAP_FILE_SHARED, 1);
	spin_unlock(&ci->i_ceph_lock);
	dout("dir_lease_is_valid dir %p v%u dentry %p v%u = %d\n",
	     dir, (unsigned)atomic_read(&ci->i_shared_gen),
	     dentry, (unsigned)di->lease_shared_gen, valid);
	return valid;
}