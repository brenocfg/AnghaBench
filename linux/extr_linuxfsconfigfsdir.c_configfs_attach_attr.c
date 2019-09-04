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
struct dentry {int /*<<< orphan*/  d_fsdata; } ;
struct configfs_dirent {int s_type; struct dentry* s_dentry; struct configfs_attribute* s_element; } ;
struct configfs_attribute {int ca_mode; } ;

/* Variables and functions */
 int CONFIGFS_ITEM_BIN_ATTR ; 
 int S_IALLUGO ; 
 int S_IFREG ; 
 int configfs_create (struct dentry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int /*<<< orphan*/  configfs_get (struct configfs_dirent*) ; 
 int /*<<< orphan*/  configfs_init_bin_file ; 
 int /*<<< orphan*/  configfs_init_file ; 
 int /*<<< orphan*/  configfs_put (struct configfs_dirent*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int configfs_attach_attr(struct configfs_dirent * sd, struct dentry * dentry)
{
	struct configfs_attribute * attr = sd->s_element;
	int error;

	spin_lock(&configfs_dirent_lock);
	dentry->d_fsdata = configfs_get(sd);
	sd->s_dentry = dentry;
	spin_unlock(&configfs_dirent_lock);

	error = configfs_create(dentry, (attr->ca_mode & S_IALLUGO) | S_IFREG,
				(sd->s_type & CONFIGFS_ITEM_BIN_ATTR) ?
					configfs_init_bin_file :
					configfs_init_file);
	if (error)
		configfs_put(sd);
	return error;
}