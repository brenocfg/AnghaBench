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
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_PRIVATE (int /*<<< orphan*/ ) ; 
 unsigned int RENAME_EXCHANGE ; 
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct inode*,struct dentry*,struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  d_backing_inode (struct dentry*) ; 
 scalar_t__ d_is_positive (struct dentry*) ; 
 int /*<<< orphan*/  inode_rename ; 
 scalar_t__ unlikely (int) ; 

int security_inode_rename(struct inode *old_dir, struct dentry *old_dentry,
			   struct inode *new_dir, struct dentry *new_dentry,
			   unsigned int flags)
{
        if (unlikely(IS_PRIVATE(d_backing_inode(old_dentry)) ||
            (d_is_positive(new_dentry) && IS_PRIVATE(d_backing_inode(new_dentry)))))
		return 0;

	if (flags & RENAME_EXCHANGE) {
		int err = call_int_hook(inode_rename, 0, new_dir, new_dentry,
						     old_dir, old_dentry);
		if (err)
			return err;
	}

	return call_int_hook(inode_rename, 0, old_dir, old_dentry,
					   new_dir, new_dentry);
}