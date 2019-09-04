#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {unsigned int i_current_depth; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  FI_INC_LINK ; 
 int /*<<< orphan*/  FI_NEW_INODE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  f2fs_i_depth_write (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  f2fs_i_links_write (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int /*<<< orphan*/ ) ; 

void f2fs_update_parent_metadata(struct inode *dir, struct inode *inode,
						unsigned int current_depth)
{
	if (inode && is_inode_flag_set(inode, FI_NEW_INODE)) {
		if (S_ISDIR(inode->i_mode))
			f2fs_i_links_write(dir, true);
		clear_inode_flag(inode, FI_NEW_INODE);
	}
	dir->i_mtime = dir->i_ctime = current_time(dir);
	f2fs_mark_inode_dirty_sync(dir, false);

	if (F2FS_I(dir)->i_current_depth != current_depth)
		f2fs_i_depth_write(dir, current_depth);

	if (inode && is_inode_flag_set(inode, FI_INC_LINK))
		clear_inode_flag(inode, FI_INC_LINK);
}