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
 int /*<<< orphan*/  OVL_XATTR_OPAQUE ; 
 int ovl_check_setxattr (struct dentry*,struct dentry*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ovl_dentry_set_opaque (struct dentry*) ; 

__attribute__((used)) static int ovl_set_opaque_xerr(struct dentry *dentry, struct dentry *upper,
			       int xerr)
{
	int err;

	err = ovl_check_setxattr(dentry, upper, OVL_XATTR_OPAQUE, "y", 1, xerr);
	if (!err)
		ovl_dentry_set_opaque(dentry);

	return err;
}