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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int reiserfs_xattr_get (struct inode*,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  reiserfs_xattrs_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xattr_full_name (struct xattr_handler const*,char const*) ; 

__attribute__((used)) static int
user_get(const struct xattr_handler *handler, struct dentry *unused,
	 struct inode *inode, const char *name, void *buffer, size_t size)
{
	if (!reiserfs_xattrs_user(inode->i_sb))
		return -EOPNOTSUPP;
	return reiserfs_xattr_get(inode, xattr_full_name(handler, name),
				  buffer, size);
}