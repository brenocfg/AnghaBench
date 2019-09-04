#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct path {int /*<<< orphan*/  mnt; struct dentry* dentry; } ;
struct open_flags {int /*<<< orphan*/  open_flag; int /*<<< orphan*/  mode; } ;
struct nameidata {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 unsigned int LOOKUP_DIRECTORY ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  audit_inode (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int finish_open (struct file*,struct dentry*,int /*<<< orphan*/ *) ; 
 int may_open (struct path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_drop_write (int /*<<< orphan*/ ) ; 
 int mnt_want_write (int /*<<< orphan*/ ) ; 
 int path_lookupat (struct nameidata*,unsigned int,struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 scalar_t__ unlikely (int) ; 
 struct dentry* vfs_tmpfile (struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_tmpfile(struct nameidata *nd, unsigned flags,
		const struct open_flags *op,
		struct file *file)
{
	struct dentry *child;
	struct path path;
	int error = path_lookupat(nd, flags | LOOKUP_DIRECTORY, &path);
	if (unlikely(error))
		return error;
	error = mnt_want_write(path.mnt);
	if (unlikely(error))
		goto out;
	child = vfs_tmpfile(path.dentry, op->mode, op->open_flag);
	error = PTR_ERR(child);
	if (IS_ERR(child))
		goto out2;
	dput(path.dentry);
	path.dentry = child;
	audit_inode(nd->name, child, 0);
	/* Don't check for other permissions, the inode was just created */
	error = may_open(&path, 0, op->open_flag);
	if (error)
		goto out2;
	file->f_path.mnt = path.mnt;
	error = finish_open(file, child, NULL);
out2:
	mnt_drop_write(path.mnt);
out:
	path_put(&path);
	return error;
}