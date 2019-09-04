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
struct dentry {int d_flags; int /*<<< orphan*/  d_sb; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int DCACHE_DISCONNECTED ; 
 int EIO ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 struct dentry* dget (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 scalar_t__ ovl_already_copied_up (struct dentry*,int) ; 
 int ovl_copy_up_one (struct dentry*,struct dentry*,int) ; 
 scalar_t__ ovl_dentry_upper (struct dentry*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 

int ovl_copy_up_flags(struct dentry *dentry, int flags)
{
	int err = 0;
	const struct cred *old_cred = ovl_override_creds(dentry->d_sb);
	bool disconnected = (dentry->d_flags & DCACHE_DISCONNECTED);

	/*
	 * With NFS export, copy up can get called for a disconnected non-dir.
	 * In this case, we will copy up lower inode to index dir without
	 * linking it to upper dir.
	 */
	if (WARN_ON(disconnected && d_is_dir(dentry)))
		return -EIO;

	while (!err) {
		struct dentry *next;
		struct dentry *parent = NULL;

		if (ovl_already_copied_up(dentry, flags))
			break;

		next = dget(dentry);
		/* find the topmost dentry not yet copied up */
		for (; !disconnected;) {
			parent = dget_parent(next);

			if (ovl_dentry_upper(parent))
				break;

			dput(next);
			next = parent;
		}

		err = ovl_copy_up_one(parent, next, flags);

		dput(parent);
		dput(next);
	}
	revert_creds(old_cred);

	return err;
}