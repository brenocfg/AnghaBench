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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip_lockres; } ;

/* Variables and functions */
 TYPE_1__* DLMFS_I (struct inode*) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,struct dentry*,...) ; 
 int simple_unlink (struct inode*,struct dentry*) ; 
 int user_dlm_destroy_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlmfs_unlink(struct inode *dir,
			struct dentry *dentry)
{
	int status;
	struct inode *inode = d_inode(dentry);

	mlog(0, "unlink inode %lu\n", inode->i_ino);

	/* if there are no current holders, or none that are waiting
	 * to acquire a lock, this basically destroys our lockres. */
	status = user_dlm_destroy_lock(&DLMFS_I(inode)->ip_lockres);
	if (status < 0) {
		mlog(ML_ERROR, "unlink %pd, error %d from destroy\n",
		     dentry, status);
		goto bail;
	}
	status = simple_unlink(dir, dentry);
bail:
	return status;
}