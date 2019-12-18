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
 int ovl_copy_up_flags (struct dentry*,int) ; 
 int /*<<< orphan*/  ovl_drop_write (struct dentry*) ; 
 scalar_t__ ovl_open_need_copy_up (struct dentry*,int) ; 
 int ovl_want_write (struct dentry*) ; 

int ovl_maybe_copy_up(struct dentry *dentry, int flags)
{
	int err = 0;

	if (ovl_open_need_copy_up(dentry, flags)) {
		err = ovl_want_write(dentry);
		if (!err) {
			err = ovl_copy_up_flags(dentry, flags);
			ovl_drop_write(dentry);
		}
	}

	return err;
}