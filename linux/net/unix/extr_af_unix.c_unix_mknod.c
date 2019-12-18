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
typedef  int /*<<< orphan*/  umode_t ;
struct path {int /*<<< orphan*/  dentry; int /*<<< orphan*/  mnt; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  done_path_create (struct path*,struct dentry*) ; 
 struct dentry* kern_path_create (int /*<<< orphan*/ ,char const*,struct path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mntget (int /*<<< orphan*/ ) ; 
 int security_path_mknod (struct path*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vfs_mknod (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unix_mknod(const char *sun_path, umode_t mode, struct path *res)
{
	struct dentry *dentry;
	struct path path;
	int err = 0;
	/*
	 * Get the parent directory, calculate the hash for last
	 * component.
	 */
	dentry = kern_path_create(AT_FDCWD, sun_path, &path, 0);
	err = PTR_ERR(dentry);
	if (IS_ERR(dentry))
		return err;

	/*
	 * All right, let's create it.
	 */
	err = security_path_mknod(&path, dentry, mode, 0);
	if (!err) {
		err = vfs_mknod(d_inode(path.dentry), dentry, mode, 0);
		if (!err) {
			res->mnt = mntget(path.mnt);
			res->dentry = dget(dentry);
		}
	}
	done_path_create(&path, dentry);
	return err;
}