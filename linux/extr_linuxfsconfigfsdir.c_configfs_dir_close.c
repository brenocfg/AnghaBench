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
struct inode {int dummy; } ;
struct TYPE_2__ {struct dentry* dentry; } ;
struct file {struct configfs_dirent* private_data; TYPE_1__ f_path; } ;
struct dentry {int dummy; } ;
struct configfs_dirent {int /*<<< orphan*/  s_sibling; } ;

/* Variables and functions */
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  inode_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_configfs_dirent (struct configfs_dirent*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int configfs_dir_close(struct inode *inode, struct file *file)
{
	struct dentry * dentry = file->f_path.dentry;
	struct configfs_dirent * cursor = file->private_data;

	inode_lock(d_inode(dentry));
	spin_lock(&configfs_dirent_lock);
	list_del_init(&cursor->s_sibling);
	spin_unlock(&configfs_dirent_lock);
	inode_unlock(d_inode(dentry));

	release_configfs_dirent(cursor);

	return 0;
}