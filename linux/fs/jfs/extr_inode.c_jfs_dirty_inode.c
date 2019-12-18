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
struct inode {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_Dirty ; 
 scalar_t__ isReadOnly (struct inode*) ; 
 int /*<<< orphan*/  jfs_err (char*) ; 
 int /*<<< orphan*/  set_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  special_file (int /*<<< orphan*/ ) ; 

void jfs_dirty_inode(struct inode *inode, int flags)
{
	static int noisy = 5;

	if (isReadOnly(inode)) {
		if (!special_file(inode->i_mode) && noisy) {
			/* kernel allows writes to devices on read-only
			 * partitions and may try to mark inode dirty
			 */
			jfs_err("jfs_dirty_inode called on read-only volume");
			jfs_err("Is remount racy?");
			noisy--;
		}
		return;
	}

	set_cflag(COMMIT_Dirty, inode);
}