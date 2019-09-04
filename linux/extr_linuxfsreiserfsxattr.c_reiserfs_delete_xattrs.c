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
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  delete_one_xattr ; 
 int reiserfs_for_each_xattr (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ ,char*,char*,int) ; 

int reiserfs_delete_xattrs(struct inode *inode)
{
	int err = reiserfs_for_each_xattr(inode, delete_one_xattr, NULL);

	if (err)
		reiserfs_warning(inode->i_sb, "jdm-20004",
				 "Couldn't delete all xattrs (%d)\n", err);
	return err;
}