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
 int /*<<< orphan*/  JFFS2_XPREFIX_SECURITY ; 
 int do_jffs2_setxattr (struct inode*,int /*<<< orphan*/ ,char const*,void const*,size_t,int) ; 

__attribute__((used)) static int jffs2_security_setxattr(const struct xattr_handler *handler,
				   struct dentry *unused, struct inode *inode,
				   const char *name, const void *buffer,
				   size_t size, int flags)
{
	return do_jffs2_setxattr(inode, JFFS2_XPREFIX_SECURITY,
				 name, buffer, size, flags);
}