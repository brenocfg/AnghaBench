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
struct kernfs_node {int dummy; } ;
struct kernfs_iattrs {int /*<<< orphan*/  xattrs; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct kernfs_node* kernfs_dentry_node (struct dentry*) ; 
 struct kernfs_iattrs* kernfs_iattrs (struct kernfs_node*) ; 
 int /*<<< orphan*/  simple_xattr_list (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,size_t) ; 

ssize_t kernfs_iop_listxattr(struct dentry *dentry, char *buf, size_t size)
{
	struct kernfs_node *kn = kernfs_dentry_node(dentry);
	struct kernfs_iattrs *attrs;

	attrs = kernfs_iattrs(kn);
	if (!attrs)
		return -ENOMEM;

	return simple_xattr_list(d_inode(dentry), &attrs->xattrs, buf, size);
}