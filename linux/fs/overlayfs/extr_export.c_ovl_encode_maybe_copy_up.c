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
 int ovl_copy_up (struct dentry*) ; 
 scalar_t__ ovl_dentry_upper (struct dentry*) ; 
 int /*<<< orphan*/  ovl_drop_write (struct dentry*) ; 
 int ovl_want_write (struct dentry*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,struct dentry*,int) ; 

__attribute__((used)) static int ovl_encode_maybe_copy_up(struct dentry *dentry)
{
	int err;

	if (ovl_dentry_upper(dentry))
		return 0;

	err = ovl_want_write(dentry);
	if (!err) {
		err = ovl_copy_up(dentry);
		ovl_drop_write(dentry);
	}

	if (err) {
		pr_warn_ratelimited("overlayfs: failed to copy up on encode (%pd2, err=%i)\n",
				    dentry, err);
	}

	return err;
}