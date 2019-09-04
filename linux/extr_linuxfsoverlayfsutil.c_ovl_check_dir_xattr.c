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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_is_dir (struct dentry*) ; 
 int vfs_getxattr (struct dentry*,char const*,char*,int) ; 

bool ovl_check_dir_xattr(struct dentry *dentry, const char *name)
{
	int res;
	char val;

	if (!d_is_dir(dentry))
		return false;

	res = vfs_getxattr(dentry, name, &val, 1);
	if (res == 1 && val == 'y')
		return true;

	return false;
}