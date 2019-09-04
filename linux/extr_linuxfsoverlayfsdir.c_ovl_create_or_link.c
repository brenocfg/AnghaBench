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
struct ovl_cattr {int /*<<< orphan*/  mode; int /*<<< orphan*/  hardlink; } ;
struct inode {int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct dentry {int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_sb; struct dentry* d_parent; } ;
struct cred {int /*<<< orphan*/  fsgid; int /*<<< orphan*/  fsuid; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct cred* override_creds (struct cred*) ; 
 int ovl_copy_up (struct dentry*) ; 
 int ovl_create_over_whiteout (struct dentry*,struct inode*,struct ovl_cattr*) ; 
 int ovl_create_upper (struct dentry*,struct inode*,struct ovl_cattr*) ; 
 int /*<<< orphan*/  ovl_dentry_is_whiteout (struct dentry*) ; 
 int /*<<< orphan*/  ovl_dentry_upper (struct dentry*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int ovl_set_impure (struct dentry*,int /*<<< orphan*/ ) ; 
 struct cred* prepare_creds () ; 
 int /*<<< orphan*/  put_cred (struct cred*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 int security_dentry_create_files_as (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct cred const*,struct cred*) ; 

__attribute__((used)) static int ovl_create_or_link(struct dentry *dentry, struct inode *inode,
			      struct ovl_cattr *attr, bool origin)
{
	int err;
	const struct cred *old_cred;
	struct cred *override_cred;
	struct dentry *parent = dentry->d_parent;

	err = ovl_copy_up(parent);
	if (err)
		return err;

	old_cred = ovl_override_creds(dentry->d_sb);

	/*
	 * When linking a file with copy up origin into a new parent, mark the
	 * new parent dir "impure".
	 */
	if (origin) {
		err = ovl_set_impure(parent, ovl_dentry_upper(parent));
		if (err)
			goto out_revert_creds;
	}

	err = -ENOMEM;
	override_cred = prepare_creds();
	if (override_cred) {
		override_cred->fsuid = inode->i_uid;
		override_cred->fsgid = inode->i_gid;
		if (!attr->hardlink) {
			err = security_dentry_create_files_as(dentry,
					attr->mode, &dentry->d_name, old_cred,
					override_cred);
			if (err) {
				put_cred(override_cred);
				goto out_revert_creds;
			}
		}
		put_cred(override_creds(override_cred));
		put_cred(override_cred);

		if (!ovl_dentry_is_whiteout(dentry))
			err = ovl_create_upper(dentry, inode, attr);
		else
			err = ovl_create_over_whiteout(dentry, inode, attr);
	}
out_revert_creds:
	revert_creds(old_cred);
	return err;
}