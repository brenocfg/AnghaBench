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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_gen (char*,char const*,int /*<<< orphan*/ ,struct dentry*,size_t) ; 
 int ubifs_xattr_remove (struct inode*,char const*) ; 
 int ubifs_xattr_set (struct inode*,char const*,void const*,size_t,int,int) ; 
 char* xattr_full_name (struct xattr_handler const*,char const*) ; 

__attribute__((used)) static int xattr_set(const struct xattr_handler *handler,
			   struct dentry *dentry, struct inode *inode,
			   const char *name, const void *value,
			   size_t size, int flags)
{
	dbg_gen("xattr '%s', host ino %lu ('%pd'), size %zd",
		name, inode->i_ino, dentry, size);

	name = xattr_full_name(handler, name);

	if (value)
		return ubifs_xattr_set(inode, name, value, size, flags, true);
	else
		return ubifs_xattr_remove(inode, name);
}