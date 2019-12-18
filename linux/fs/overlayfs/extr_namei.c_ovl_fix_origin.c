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
struct dentry {int /*<<< orphan*/  d_parent; } ;

/* Variables and functions */
 scalar_t__ ovl_check_origin_xattr (struct dentry*) ; 
 int /*<<< orphan*/  ovl_drop_write (struct dentry*) ; 
 int ovl_set_impure (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ovl_set_origin (struct dentry*,struct dentry*,struct dentry*) ; 
 int ovl_want_write (struct dentry*) ; 

__attribute__((used)) static int ovl_fix_origin(struct dentry *dentry, struct dentry *lower,
			  struct dentry *upper)
{
	int err;

	if (ovl_check_origin_xattr(upper))
		return 0;

	err = ovl_want_write(dentry);
	if (err)
		return err;

	err = ovl_set_origin(dentry, lower, upper);
	if (!err)
		err = ovl_set_impure(dentry->d_parent, upper->d_parent);

	ovl_drop_write(dentry);
	return err;
}