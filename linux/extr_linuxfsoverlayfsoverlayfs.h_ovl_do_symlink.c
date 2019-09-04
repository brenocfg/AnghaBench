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
 int /*<<< orphan*/  pr_debug (char*,char const*,struct dentry*,int) ; 
 int vfs_symlink (struct inode*,struct dentry*,char const*) ; 

__attribute__((used)) static inline int ovl_do_symlink(struct inode *dir, struct dentry *dentry,
				 const char *oldname)
{
	int err = vfs_symlink(dir, dentry, oldname);

	pr_debug("symlink(\"%s\", %pd2) = %i\n", oldname, dentry, err);
	return err;
}