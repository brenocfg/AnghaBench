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
struct name_snapshot {int /*<<< orphan*/  name; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 scalar_t__ IS_ERR_OR_NULL (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_is_dir (struct dentry*) ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 
 int /*<<< orphan*/  d_move (struct dentry*,struct dentry*) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dentry*) ; 
 struct dentry* lock_rename (struct dentry*,struct dentry*) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_dentry_name_snapshot (struct name_snapshot*) ; 
 int simple_rename (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  take_dentry_name_snapshot (struct name_snapshot*,struct dentry*) ; 
 int /*<<< orphan*/  unlock_rename (struct dentry*,struct dentry*) ; 

struct dentry *debugfs_rename(struct dentry *old_dir, struct dentry *old_dentry,
		struct dentry *new_dir, const char *new_name)
{
	int error;
	struct dentry *dentry = NULL, *trap;
	struct name_snapshot old_name;

	if (IS_ERR(old_dir))
		return old_dir;
	if (IS_ERR(new_dir))
		return new_dir;
	if (IS_ERR_OR_NULL(old_dentry))
		return old_dentry;

	trap = lock_rename(new_dir, old_dir);
	/* Source or destination directories don't exist? */
	if (d_really_is_negative(old_dir) || d_really_is_negative(new_dir))
		goto exit;
	/* Source does not exist, cyclic rename, or mountpoint? */
	if (d_really_is_negative(old_dentry) || old_dentry == trap ||
	    d_mountpoint(old_dentry))
		goto exit;
	dentry = lookup_one_len(new_name, new_dir, strlen(new_name));
	/* Lookup failed, cyclic rename or target exists? */
	if (IS_ERR(dentry) || dentry == trap || d_really_is_positive(dentry))
		goto exit;

	take_dentry_name_snapshot(&old_name, old_dentry);

	error = simple_rename(d_inode(old_dir), old_dentry, d_inode(new_dir),
			      dentry, 0);
	if (error) {
		release_dentry_name_snapshot(&old_name);
		goto exit;
	}
	d_move(old_dentry, dentry);
	fsnotify_move(d_inode(old_dir), d_inode(new_dir), &old_name.name,
		d_is_dir(old_dentry),
		NULL, old_dentry);
	release_dentry_name_snapshot(&old_name);
	unlock_rename(new_dir, old_dir);
	dput(dentry);
	return old_dentry;
exit:
	if (dentry && !IS_ERR(dentry))
		dput(dentry);
	unlock_rename(new_dir, old_dir);
	if (IS_ERR(dentry))
		return dentry;
	return ERR_PTR(-EINVAL);
}