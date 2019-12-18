#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dentry {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_6__ {TYPE_1__* i_op; } ;
struct TYPE_5__ {int (* listxattr ) (struct dentry*,char*,size_t) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 TYPE_2__* d_inode (struct dentry*) ; 
 struct dentry* ecryptfs_dentry_to_lower (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  inode_unlock (TYPE_2__*) ; 
 int stub1 (struct dentry*,char*,size_t) ; 

__attribute__((used)) static ssize_t
ecryptfs_listxattr(struct dentry *dentry, char *list, size_t size)
{
	int rc = 0;
	struct dentry *lower_dentry;

	lower_dentry = ecryptfs_dentry_to_lower(dentry);
	if (!d_inode(lower_dentry)->i_op->listxattr) {
		rc = -EOPNOTSUPP;
		goto out;
	}
	inode_lock(d_inode(lower_dentry));
	rc = d_inode(lower_dentry)->i_op->listxattr(lower_dentry, list, size);
	inode_unlock(d_inode(lower_dentry));
out:
	return rc;
}