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
 int /*<<< orphan*/  FI_NEW_INODE ; 
 scalar_t__ f2fs_inode_dirtied (struct inode*,int) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_inode_dirty_sync (struct inode*) ; 

void f2fs_mark_inode_dirty_sync(struct inode *inode, bool sync)
{
	if (is_inode_flag_set(inode, FI_NEW_INODE))
		return;

	if (f2fs_inode_dirtied(inode, sync))
		return;

	mark_inode_dirty_sync(inode);
}