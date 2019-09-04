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
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int RENAME_EXCHANGE ; 
 scalar_t__ d_is_dir (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  ovl_cleanup (struct inode*,struct dentry*) ; 
 int ovl_do_rename (struct inode*,struct dentry*,struct inode*,struct dentry*,int) ; 
 struct dentry* ovl_whiteout (struct dentry*) ; 

int ovl_cleanup_and_whiteout(struct dentry *workdir, struct inode *dir,
			     struct dentry *dentry)
{
	struct inode *wdir = workdir->d_inode;
	struct dentry *whiteout;
	int err;
	int flags = 0;

	whiteout = ovl_whiteout(workdir);
	err = PTR_ERR(whiteout);
	if (IS_ERR(whiteout))
		return err;

	if (d_is_dir(dentry))
		flags = RENAME_EXCHANGE;

	err = ovl_do_rename(wdir, whiteout, dir, dentry, flags);
	if (err)
		goto kill_whiteout;
	if (flags)
		ovl_cleanup(wdir, dentry);

out:
	dput(whiteout);
	return err;

kill_whiteout:
	ovl_cleanup(wdir, whiteout);
	goto out;
}