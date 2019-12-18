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
struct dentry {int /*<<< orphan*/  d_inode; int /*<<< orphan*/  d_sb; int /*<<< orphan*/  d_parent; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_nlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  ovl_cache_free (int /*<<< orphan*/ *) ; 
 int ovl_check_empty_dir (struct dentry*,int /*<<< orphan*/ *) ; 
 int ovl_copy_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_copyattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dentry* ovl_dentry_upper (struct dentry*) ; 
 int /*<<< orphan*/  ovl_drop_write (struct dentry*) ; 
 int ovl_lower_positive (struct dentry*) ; 
 int /*<<< orphan*/  ovl_nlink_end (struct dentry*) ; 
 int ovl_nlink_start (struct dentry*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovl_pure_upper (struct dentry*) ; 
 int ovl_remove_and_whiteout (struct dentry*,int /*<<< orphan*/ *) ; 
 int ovl_remove_upper (struct dentry*,int,int /*<<< orphan*/ *) ; 
 int ovl_want_write (struct dentry*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 

__attribute__((used)) static int ovl_do_remove(struct dentry *dentry, bool is_dir)
{
	int err;
	const struct cred *old_cred;
	struct dentry *upperdentry;
	bool lower_positive = ovl_lower_positive(dentry);
	LIST_HEAD(list);

	/* No need to clean pure upper removed by vfs_rmdir() */
	if (is_dir && (lower_positive || !ovl_pure_upper(dentry))) {
		err = ovl_check_empty_dir(dentry, &list);
		if (err)
			goto out;
	}

	err = ovl_want_write(dentry);
	if (err)
		goto out;

	err = ovl_copy_up(dentry->d_parent);
	if (err)
		goto out_drop_write;

	err = ovl_nlink_start(dentry);
	if (err)
		goto out_drop_write;

	old_cred = ovl_override_creds(dentry->d_sb);
	if (!lower_positive)
		err = ovl_remove_upper(dentry, is_dir, &list);
	else
		err = ovl_remove_and_whiteout(dentry, &list);
	revert_creds(old_cred);
	if (!err) {
		if (is_dir)
			clear_nlink(dentry->d_inode);
		else
			drop_nlink(dentry->d_inode);
	}
	ovl_nlink_end(dentry);

	/*
	 * Copy ctime
	 *
	 * Note: we fail to update ctime if there was no copy-up, only a
	 * whiteout
	 */
	upperdentry = ovl_dentry_upper(dentry);
	if (upperdentry)
		ovl_copyattr(d_inode(upperdentry), d_inode(dentry));

out_drop_write:
	ovl_drop_write(dentry);
out:
	ovl_cache_free(&list);
	return err;
}