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
 int /*<<< orphan*/  pr_debug (char*,struct dentry*,int) ; 
 int vfs_rmdir (struct inode*,struct dentry*) ; 

__attribute__((used)) static inline int ovl_do_rmdir(struct inode *dir, struct dentry *dentry)
{
	int err = vfs_rmdir(dir, dentry);

	pr_debug("rmdir(%pd2) = %i\n", dentry, err);
	return err;
}