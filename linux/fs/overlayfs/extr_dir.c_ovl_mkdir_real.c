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
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 scalar_t__ likely (int) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ovl_do_mkdir (struct inode*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,struct dentry*,int) ; 

__attribute__((used)) static int ovl_mkdir_real(struct inode *dir, struct dentry **newdentry,
			  umode_t mode)
{
	int err;
	struct dentry *d, *dentry = *newdentry;

	err = ovl_do_mkdir(dir, dentry, mode);
	if (err)
		return err;

	if (likely(!d_unhashed(dentry)))
		return 0;

	/*
	 * vfs_mkdir() may succeed and leave the dentry passed
	 * to it unhashed and negative. If that happens, try to
	 * lookup a new hashed and positive dentry.
	 */
	d = lookup_one_len(dentry->d_name.name, dentry->d_parent,
			   dentry->d_name.len);
	if (IS_ERR(d)) {
		pr_warn("overlayfs: failed lookup after mkdir (%pd2, err=%i).\n",
			dentry, err);
		return PTR_ERR(d);
	}
	dput(dentry);
	*newdentry = d;

	return 0;
}