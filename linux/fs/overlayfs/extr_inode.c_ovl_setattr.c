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
struct inode {int /*<<< orphan*/  i_writecount; } ;
struct iattr {int ia_valid; } ;
struct dentry {int /*<<< orphan*/  d_inode; int /*<<< orphan*/  d_sb; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int ATTR_KILL_SGID ; 
 int ATTR_KILL_SUID ; 
 int ATTR_MODE ; 
 int ATTR_SIZE ; 
 int ETXTBSY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct inode* d_inode (struct dentry*) ; 
 int get_write_access (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int notify_change (struct dentry*,struct iattr*,int /*<<< orphan*/ *) ; 
 int ovl_copy_up (struct dentry*) ; 
 int ovl_copy_up_with_data (struct dentry*) ; 
 int /*<<< orphan*/  ovl_copyattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dentry* ovl_dentry_real (struct dentry*) ; 
 struct dentry* ovl_dentry_upper (struct dentry*) ; 
 int /*<<< orphan*/  ovl_drop_write (struct dentry*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int ovl_want_write (struct dentry*) ; 
 int /*<<< orphan*/  put_write_access (struct inode*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 

int ovl_setattr(struct dentry *dentry, struct iattr *attr)
{
	int err;
	bool full_copy_up = false;
	struct dentry *upperdentry;
	const struct cred *old_cred;

	err = setattr_prepare(dentry, attr);
	if (err)
		return err;

	err = ovl_want_write(dentry);
	if (err)
		goto out;

	if (attr->ia_valid & ATTR_SIZE) {
		struct inode *realinode = d_inode(ovl_dentry_real(dentry));

		err = -ETXTBSY;
		if (atomic_read(&realinode->i_writecount) < 0)
			goto out_drop_write;

		/* Truncate should trigger data copy up as well */
		full_copy_up = true;
	}

	if (!full_copy_up)
		err = ovl_copy_up(dentry);
	else
		err = ovl_copy_up_with_data(dentry);
	if (!err) {
		struct inode *winode = NULL;

		upperdentry = ovl_dentry_upper(dentry);

		if (attr->ia_valid & ATTR_SIZE) {
			winode = d_inode(upperdentry);
			err = get_write_access(winode);
			if (err)
				goto out_drop_write;
		}

		if (attr->ia_valid & (ATTR_KILL_SUID|ATTR_KILL_SGID))
			attr->ia_valid &= ~ATTR_MODE;

		inode_lock(upperdentry->d_inode);
		old_cred = ovl_override_creds(dentry->d_sb);
		err = notify_change(upperdentry, attr, NULL);
		revert_creds(old_cred);
		if (!err)
			ovl_copyattr(upperdentry->d_inode, dentry->d_inode);
		inode_unlock(upperdentry->d_inode);

		if (winode)
			put_write_access(winode);
	}
out_drop_write:
	ovl_drop_write(dentry);
out:
	return err;
}