#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ohandle; int /*<<< orphan*/  ohandlen; } ;
typedef  TYPE_1__ xfs_fsop_handlereq_t ;
struct file {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EFAULT ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  d_is_symlink (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int vfs_readlink (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dentry* xfs_handlereq_to_dentry (struct file*,TYPE_1__*) ; 

int
xfs_readlink_by_handle(
	struct file		*parfilp,
	xfs_fsop_handlereq_t	*hreq)
{
	struct dentry		*dentry;
	__u32			olen;
	int			error;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	dentry = xfs_handlereq_to_dentry(parfilp, hreq);
	if (IS_ERR(dentry))
		return PTR_ERR(dentry);

	/* Restrict this handle operation to symlinks only. */
	if (!d_is_symlink(dentry)) {
		error = -EINVAL;
		goto out_dput;
	}

	if (copy_from_user(&olen, hreq->ohandlen, sizeof(__u32))) {
		error = -EFAULT;
		goto out_dput;
	}

	error = vfs_readlink(dentry, hreq->ohandle, olen);

 out_dput:
	dput(dentry);
	return error;
}