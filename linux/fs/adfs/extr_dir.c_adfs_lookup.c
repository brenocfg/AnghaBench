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
struct object_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOENT ; 
 struct inode* ERR_PTR (int) ; 
 int adfs_dir_lookup_byname (struct inode*,int /*<<< orphan*/ *,struct object_info*) ; 
 struct inode* adfs_iget (int /*<<< orphan*/ ,struct object_info*) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 

__attribute__((used)) static struct dentry *
adfs_lookup(struct inode *dir, struct dentry *dentry, unsigned int flags)
{
	struct inode *inode = NULL;
	struct object_info obj;
	int error;

	error = adfs_dir_lookup_byname(dir, &dentry->d_name, &obj);
	if (error == 0) {
		/*
		 * This only returns NULL if get_empty_inode
		 * fails.
		 */
		inode = adfs_iget(dir->i_sb, &obj);
		if (!inode)
			inode = ERR_PTR(-EACCES);
	} else if (error != -ENOENT) {
		inode = ERR_PTR(error);
	}
	return d_splice_alias(inode, dentry);
}