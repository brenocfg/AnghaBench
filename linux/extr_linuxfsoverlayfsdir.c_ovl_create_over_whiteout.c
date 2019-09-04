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
struct posix_acl {int dummy; } ;
struct ovl_cattr {scalar_t__ mode; int /*<<< orphan*/  hardlink; } ;
struct inode {scalar_t__ i_mode; } ;
struct iattr {scalar_t__ ia_mode; int /*<<< orphan*/  ia_valid; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {struct inode* d_inode; TYPE_1__ d_name; TYPE_2__* d_parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_MODE ; 
 int EROFS ; 
 int ESTALE ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  IS_WHITEOUT (int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  RENAME_EXCHANGE ; 
 scalar_t__ S_ISDIR (scalar_t__) ; 
 int /*<<< orphan*/  S_ISLNK (scalar_t__) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  XATTR_NAME_POSIX_ACL_ACCESS ; 
 int /*<<< orphan*/  XATTR_NAME_POSIX_ACL_DEFAULT ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_is_negative (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int notify_change (struct dentry*,struct iattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ovl_cleanup (struct inode*,struct dentry*) ; 
 struct dentry* ovl_create_temp (struct dentry*,struct ovl_cattr*) ; 
 struct dentry* ovl_dentry_upper (TYPE_2__*) ; 
 int ovl_do_rename (struct inode*,struct dentry*,struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int ovl_instantiate (struct dentry*,struct inode*,struct dentry*,int) ; 
 int ovl_lock_rename_workdir (struct dentry*,struct dentry*) ; 
 int ovl_set_opaque (struct dentry*,struct dentry*) ; 
 int ovl_set_upper_acl (struct dentry*,int /*<<< orphan*/ ,struct posix_acl*) ; 
 struct dentry* ovl_workdir (struct dentry*) ; 
 int posix_acl_create (int /*<<< orphan*/ ,scalar_t__*,struct posix_acl**,struct posix_acl**) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int /*<<< orphan*/  unlock_rename (struct dentry*,struct dentry*) ; 

__attribute__((used)) static int ovl_create_over_whiteout(struct dentry *dentry, struct inode *inode,
				    struct ovl_cattr *cattr)
{
	struct dentry *workdir = ovl_workdir(dentry);
	struct inode *wdir = workdir->d_inode;
	struct dentry *upperdir = ovl_dentry_upper(dentry->d_parent);
	struct inode *udir = upperdir->d_inode;
	struct dentry *upper;
	struct dentry *newdentry;
	int err;
	struct posix_acl *acl, *default_acl;
	bool hardlink = !!cattr->hardlink;

	if (WARN_ON(!workdir))
		return -EROFS;

	if (!hardlink) {
		err = posix_acl_create(dentry->d_parent->d_inode,
				       &cattr->mode, &default_acl, &acl);
		if (err)
			return err;
	}

	err = ovl_lock_rename_workdir(workdir, upperdir);
	if (err)
		goto out;

	upper = lookup_one_len(dentry->d_name.name, upperdir,
			       dentry->d_name.len);
	err = PTR_ERR(upper);
	if (IS_ERR(upper))
		goto out_unlock;

	err = -ESTALE;
	if (d_is_negative(upper) || !IS_WHITEOUT(d_inode(upper)))
		goto out_dput;

	newdentry = ovl_create_temp(workdir, cattr);
	err = PTR_ERR(newdentry);
	if (IS_ERR(newdentry))
		goto out_dput;

	/*
	 * mode could have been mutilated due to umask (e.g. sgid directory)
	 */
	if (!hardlink &&
	    !S_ISLNK(cattr->mode) &&
	    newdentry->d_inode->i_mode != cattr->mode) {
		struct iattr attr = {
			.ia_valid = ATTR_MODE,
			.ia_mode = cattr->mode,
		};
		inode_lock(newdentry->d_inode);
		err = notify_change(newdentry, &attr, NULL);
		inode_unlock(newdentry->d_inode);
		if (err)
			goto out_cleanup;
	}
	if (!hardlink) {
		err = ovl_set_upper_acl(newdentry, XATTR_NAME_POSIX_ACL_ACCESS,
					acl);
		if (err)
			goto out_cleanup;

		err = ovl_set_upper_acl(newdentry, XATTR_NAME_POSIX_ACL_DEFAULT,
					default_acl);
		if (err)
			goto out_cleanup;
	}

	if (!hardlink && S_ISDIR(cattr->mode)) {
		err = ovl_set_opaque(dentry, newdentry);
		if (err)
			goto out_cleanup;

		err = ovl_do_rename(wdir, newdentry, udir, upper,
				    RENAME_EXCHANGE);
		if (err)
			goto out_cleanup;

		ovl_cleanup(wdir, upper);
	} else {
		err = ovl_do_rename(wdir, newdentry, udir, upper, 0);
		if (err)
			goto out_cleanup;
	}
	err = ovl_instantiate(dentry, inode, newdentry, hardlink);
	if (err)
		goto out_cleanup;
out_dput:
	dput(upper);
out_unlock:
	unlock_rename(workdir, upperdir);
out:
	if (!hardlink) {
		posix_acl_release(acl);
		posix_acl_release(default_acl);
	}
	return err;

out_cleanup:
	ovl_cleanup(wdir, newdentry);
	dput(newdentry);
	goto out_dput;
}