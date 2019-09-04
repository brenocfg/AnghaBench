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
struct ovl_inode {int /*<<< orphan*/  lock; } ;
struct dentry {int /*<<< orphan*/  d_sb; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 struct ovl_inode* OVL_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OVL_INDEX ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ovl_copy_up (struct dentry*) ; 
 int /*<<< orphan*/  ovl_dentry_has_upper_alias (struct dentry*) ; 
 scalar_t__ ovl_need_index (struct dentry*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int ovl_set_nlink_upper (struct dentry*) ; 
 int /*<<< orphan*/  ovl_test_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 

int ovl_nlink_start(struct dentry *dentry, bool *locked)
{
	struct ovl_inode *oi = OVL_I(d_inode(dentry));
	const struct cred *old_cred;
	int err;

	if (!d_inode(dentry))
		return 0;

	/*
	 * With inodes index is enabled, we store the union overlay nlink
	 * in an xattr on the index inode. When whiting out an indexed lower,
	 * we need to decrement the overlay persistent nlink, but before the
	 * first copy up, we have no upper index inode to store the xattr.
	 *
	 * As a workaround, before whiteout/rename over an indexed lower,
	 * copy up to create the upper index. Creating the upper index will
	 * initialize the overlay nlink, so it could be dropped if unlink
	 * or rename succeeds.
	 *
	 * TODO: implement metadata only index copy up when called with
	 *       ovl_copy_up_flags(dentry, O_PATH).
	 */
	if (ovl_need_index(dentry) && !ovl_dentry_has_upper_alias(dentry)) {
		err = ovl_copy_up(dentry);
		if (err)
			return err;
	}

	err = mutex_lock_interruptible(&oi->lock);
	if (err)
		return err;

	if (d_is_dir(dentry) || !ovl_test_flag(OVL_INDEX, d_inode(dentry)))
		goto out;

	old_cred = ovl_override_creds(dentry->d_sb);
	/*
	 * The overlay inode nlink should be incremented/decremented IFF the
	 * upper operation succeeds, along with nlink change of upper inode.
	 * Therefore, before link/unlink/rename, we store the union nlink
	 * value relative to the upper inode nlink in an upper inode xattr.
	 */
	err = ovl_set_nlink_upper(dentry);
	revert_creds(old_cred);

out:
	if (err)
		mutex_unlock(&oi->lock);
	else
		*locked = true;

	return err;
}