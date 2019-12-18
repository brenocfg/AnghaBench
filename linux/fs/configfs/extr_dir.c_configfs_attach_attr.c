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
struct inode {int /*<<< orphan*/ * i_fop; scalar_t__ i_size; } ;
struct dentry {int /*<<< orphan*/  d_fsdata; } ;
struct configfs_dirent {int s_type; struct dentry* s_dentry; struct configfs_attribute* s_element; } ;
struct configfs_attribute {int ca_mode; } ;

/* Variables and functions */
 int CONFIGFS_ITEM_BIN_ATTR ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ PAGE_SIZE ; 
 int PTR_ERR (struct inode*) ; 
 int S_IALLUGO ; 
 int S_IFREG ; 
 int /*<<< orphan*/  configfs_bin_file_operations ; 
 struct inode* configfs_create (struct dentry*,int) ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int /*<<< orphan*/  configfs_file_operations ; 
 int /*<<< orphan*/  configfs_get (struct configfs_dirent*) ; 
 int /*<<< orphan*/  configfs_put (struct configfs_dirent*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int configfs_attach_attr(struct configfs_dirent * sd, struct dentry * dentry)
{
	struct configfs_attribute * attr = sd->s_element;
	struct inode *inode;

	spin_lock(&configfs_dirent_lock);
	dentry->d_fsdata = configfs_get(sd);
	sd->s_dentry = dentry;
	spin_unlock(&configfs_dirent_lock);

	inode = configfs_create(dentry, (attr->ca_mode & S_IALLUGO) | S_IFREG);
	if (IS_ERR(inode)) {
		configfs_put(sd);
		return PTR_ERR(inode);
	}
	if (sd->s_type & CONFIGFS_ITEM_BIN_ATTR) {
		inode->i_size = 0;
		inode->i_fop = &configfs_bin_file_operations;
	} else {
		inode->i_size = PAGE_SIZE;
		inode->i_fop = &configfs_file_operations;
	}
	d_add(dentry, inode);
	return 0;
}