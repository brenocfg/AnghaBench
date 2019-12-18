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
typedef  int umode_t ;
struct qstr {scalar_t__ len; char* name; } ;
struct inode {int dummy; } ;
struct dentry {struct qstr d_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int S_IFREG ; 
 scalar_t__ USER_DLM_LOCK_ID_MAX_LEN ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 struct inode* dlmfs_get_inode (struct inode*,struct dentry*,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 

__attribute__((used)) static int dlmfs_create(struct inode *dir,
			struct dentry *dentry,
			umode_t mode,
			bool excl)
{
	int status = 0;
	struct inode *inode;
	const struct qstr *name = &dentry->d_name;

	mlog(0, "create %.*s\n", name->len, name->name);

	/* verify name is valid and doesn't contain any dlm reserved
	 * characters */
	if (name->len >= USER_DLM_LOCK_ID_MAX_LEN ||
	    name->name[0] == '$') {
		status = -EINVAL;
		mlog(ML_ERROR, "invalid lock name, %.*s\n", name->len,
		     name->name);
		goto bail;
	}

	inode = dlmfs_get_inode(dir, dentry, mode | S_IFREG);
	if (!inode) {
		status = -ENOMEM;
		mlog_errno(status);
		goto bail;
	}

	d_instantiate(dentry, inode);
	dget(dentry);	/* Extra count - pin the dentry in core */
bail:
	return status;
}