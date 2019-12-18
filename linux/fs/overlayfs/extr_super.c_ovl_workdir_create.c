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
struct vfsmount {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  workdir; } ;
struct ovl_fs {TYPE_1__ config; TYPE_2__* workbasedir; struct vfsmount* upper_mnt; } ;
struct inode {int dummy; } ;
struct iattr {int ia_mode; int /*<<< orphan*/  ia_valid; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_MODE ; 
 int EEXIST ; 
 int ENODATA ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  I_MUTEX_PARENT ; 
 int /*<<< orphan*/  OVL_CATTR (int) ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  XATTR_NAME_POSIX_ACL_ACCESS ; 
 int /*<<< orphan*/  XATTR_NAME_POSIX_ACL_DEFAULT ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 struct dentry* lookup_one_len (char const*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int notify_change (struct dentry*,struct iattr*,int /*<<< orphan*/ *) ; 
 struct dentry* ovl_create_real (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_workdir_cleanup (struct inode*,struct vfsmount*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int vfs_removexattr (struct dentry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *ovl_workdir_create(struct ovl_fs *ofs,
					 const char *name, bool persist)
{
	struct inode *dir =  ofs->workbasedir->d_inode;
	struct vfsmount *mnt = ofs->upper_mnt;
	struct dentry *work;
	int err;
	bool retried = false;
	bool locked = false;

	inode_lock_nested(dir, I_MUTEX_PARENT);
	locked = true;

retry:
	work = lookup_one_len(name, ofs->workbasedir, strlen(name));

	if (!IS_ERR(work)) {
		struct iattr attr = {
			.ia_valid = ATTR_MODE,
			.ia_mode = S_IFDIR | 0,
		};

		if (work->d_inode) {
			err = -EEXIST;
			if (retried)
				goto out_dput;

			if (persist)
				goto out_unlock;

			retried = true;
			ovl_workdir_cleanup(dir, mnt, work, 0);
			dput(work);
			goto retry;
		}

		work = ovl_create_real(dir, work, OVL_CATTR(attr.ia_mode));
		err = PTR_ERR(work);
		if (IS_ERR(work))
			goto out_err;

		/*
		 * Try to remove POSIX ACL xattrs from workdir.  We are good if:
		 *
		 * a) success (there was a POSIX ACL xattr and was removed)
		 * b) -ENODATA (there was no POSIX ACL xattr)
		 * c) -EOPNOTSUPP (POSIX ACL xattrs are not supported)
		 *
		 * There are various other error values that could effectively
		 * mean that the xattr doesn't exist (e.g. -ERANGE is returned
		 * if the xattr name is too long), but the set of filesystems
		 * allowed as upper are limited to "normal" ones, where checking
		 * for the above two errors is sufficient.
		 */
		err = vfs_removexattr(work, XATTR_NAME_POSIX_ACL_DEFAULT);
		if (err && err != -ENODATA && err != -EOPNOTSUPP)
			goto out_dput;

		err = vfs_removexattr(work, XATTR_NAME_POSIX_ACL_ACCESS);
		if (err && err != -ENODATA && err != -EOPNOTSUPP)
			goto out_dput;

		/* Clear any inherited mode bits */
		inode_lock(work->d_inode);
		err = notify_change(work, &attr, NULL);
		inode_unlock(work->d_inode);
		if (err)
			goto out_dput;
	} else {
		err = PTR_ERR(work);
		goto out_err;
	}
out_unlock:
	if (locked)
		inode_unlock(dir);

	return work;

out_dput:
	dput(work);
out_err:
	pr_warn("overlayfs: failed to create directory %s/%s (errno: %i); mounting read-only\n",
		ofs->config.workdir, name, -err);
	work = NULL;
	goto out_unlock;
}