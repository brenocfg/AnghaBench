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
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int ovl_do_whiteout (struct inode*,struct dentry*) ; 
 struct dentry* ovl_lookup_temp (struct dentry*) ; 

__attribute__((used)) static struct dentry *ovl_whiteout(struct dentry *workdir)
{
	int err;
	struct dentry *whiteout;
	struct inode *wdir = workdir->d_inode;

	whiteout = ovl_lookup_temp(workdir);
	if (IS_ERR(whiteout))
		return whiteout;

	err = ovl_do_whiteout(wdir, whiteout);
	if (err) {
		dput(whiteout);
		whiteout = ERR_PTR(err);
	}

	return whiteout;
}