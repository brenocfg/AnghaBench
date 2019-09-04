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
struct configfs_dirent {int /*<<< orphan*/ * s_dentry; int /*<<< orphan*/  s_count; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
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
		/* Coordinate with configfs_attach_attr where will increase
		 * sd->s_count and update sd->s_dentry to new allocated one.
		 * Only set sd->dentry to null when this dentry is the only
		 * sd owner.
		 * If not do so, configfs_d_iput may run just after
		 * configfs_attach_attr and set sd->s_dentry to null
		 * even it's still in use.
		 */
		if (atomic_read(&sd->s_count) <= 2)
			sd->s_dentry = NULL;

		spin_unlock(&configfs_dirent_lock);
		configfs_put(sd);
	}
	iput(inode);
}