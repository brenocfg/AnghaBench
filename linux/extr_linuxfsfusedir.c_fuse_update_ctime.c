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
struct inode {int /*<<< orphan*/  i_ctime; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_NOCMTIME (struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty_sync (struct inode*) ; 

void fuse_update_ctime(struct inode *inode)
{
	if (!IS_NOCMTIME(inode)) {
		inode->i_ctime = current_time(inode);
		mark_inode_dirty_sync(inode);
	}
}