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
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ d_is_dir (struct dentry*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int ovl_do_rmdir (struct inode*,struct dentry*) ; 
 int ovl_do_unlink (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  pr_err (char*,struct dentry*,int) ; 

int ovl_cleanup(struct inode *wdir, struct dentry *wdentry)
{
	int err;

	dget(wdentry);
	if (d_is_dir(wdentry))
		err = ovl_do_rmdir(wdir, wdentry);
	else
		err = ovl_do_unlink(wdir, wdentry);
	dput(wdentry);

	if (err) {
		pr_err("overlayfs: cleanup of '%pd2' failed (%i)\n",
		       wdentry, err);
	}

	return err;
}