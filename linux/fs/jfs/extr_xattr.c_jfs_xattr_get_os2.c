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
struct xattr_handler {int dummy; } ;
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int __jfs_getxattr (struct inode*,char const*,void*,size_t) ; 
 scalar_t__ is_known_namespace (char const*) ; 

__attribute__((used)) static int jfs_xattr_get_os2(const struct xattr_handler *handler,
			     struct dentry *unused, struct inode *inode,
			     const char *name, void *value, size_t size)
{
	if (is_known_namespace(name))
		return -EOPNOTSUPP;
	return __jfs_getxattr(inode, name, value, size);
}