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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HFSPLUS_ATTR_MAX_STRLEN ; 
 int NLS_MAX_CHARSET_SIZE ; 
 int __hfsplus_setxattr (struct inode*,char*,void const*,size_t,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

int hfsplus_setxattr(struct inode *inode, const char *name,
		     const void *value, size_t size, int flags,
		     const char *prefix, size_t prefixlen)
{
	char *xattr_name;
	int res;

	xattr_name = kmalloc(NLS_MAX_CHARSET_SIZE * HFSPLUS_ATTR_MAX_STRLEN + 1,
		GFP_KERNEL);
	if (!xattr_name)
		return -ENOMEM;
	strcpy(xattr_name, prefix);
	strcpy(xattr_name + prefixlen, name);
	res = __hfsplus_setxattr(inode, xattr_name, value, size, flags);
	kfree(xattr_name);
	return res;
}