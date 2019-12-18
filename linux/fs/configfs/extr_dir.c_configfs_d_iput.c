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
struct dentry {struct configfs_dirent* d_fsdata; } ;
struct configfs_dirent {struct dentry* s_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int /*<<< orphan*/  configfs_put (struct configfs_dirent*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void configfs_d_iput(struct dentry * dentry,
			    struct inode * inode)
{
	struct configfs_dirent *sd = dentry->d_fsdata;

	if (sd) {
		/* Coordinate with configfs_readdir */
		spin_lock(&configfs_dirent_lock);
		/*
		 * Set sd->s_dentry to null only when this dentry is the one
		 * that is going to be killed.  Otherwise configfs_d_iput may
		 * run just after configfs_attach_attr and set sd->s_dentry to
		 * NULL even it's still in use.
		 */
		if (sd->s_dentry == dentry)
			sd->s_dentry = NULL;

		spin_unlock(&configfs_dirent_lock);
		configfs_put(sd);
	}
	iput(inode);
}