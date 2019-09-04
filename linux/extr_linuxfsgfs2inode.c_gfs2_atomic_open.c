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
typedef  int umode_t ;
struct inode {int dummy; } ;
struct file {int f_mode; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int FMODE_OPENED ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 unsigned int O_CREAT ; 
 unsigned int O_EXCL ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IFREG ; 
 struct dentry* __gfs2_lookup (struct inode*,struct dentry*,struct file*) ; 
 int /*<<< orphan*/  d_in_lookup (struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int finish_no_open (struct file*,struct dentry*) ; 
 int gfs2_create_inode (struct inode*,struct dentry*,struct file*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gfs2_atomic_open(struct inode *dir, struct dentry *dentry,
			    struct file *file, unsigned flags,
			    umode_t mode)
{
	struct dentry *d;
	bool excl = !!(flags & O_EXCL);

	if (!d_in_lookup(dentry))
		goto skip_lookup;

	d = __gfs2_lookup(dir, dentry, file);
	if (IS_ERR(d))
		return PTR_ERR(d);
	if (d != NULL)
		dentry = d;
	if (d_really_is_positive(dentry)) {
		if (!(file->f_mode & FMODE_OPENED))
			return finish_no_open(file, d);
		dput(d);
		return 0;
	}

	BUG_ON(d != NULL);

skip_lookup:
	if (!(flags & O_CREAT))
		return -ENOENT;

	return gfs2_create_inode(dir, dentry, file, S_IFREG | mode, 0, NULL, 0, excl);
}