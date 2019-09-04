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
struct inode {int dummy; } ;
struct f2fs_sb_info {int /*<<< orphan*/ * inode_list; } ;
typedef  enum inode_type { ____Placeholder_inode_type } inode_type ;
struct TYPE_2__ {int /*<<< orphan*/  dirty_list; } ;

/* Variables and functions */
 int DIR_INODE ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int FI_DIRTY_DIR ; 
 int FI_DIRTY_FILE ; 
 int /*<<< orphan*/  f2fs_is_volatile_file (struct inode*) ; 
 scalar_t__ is_inode_flag_set (struct inode*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int) ; 
 int /*<<< orphan*/  stat_inc_dirty_inode (struct f2fs_sb_info*,int) ; 

__attribute__((used)) static void __add_dirty_inode(struct inode *inode, enum inode_type type)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	int flag = (type == DIR_INODE) ? FI_DIRTY_DIR : FI_DIRTY_FILE;

	if (is_inode_flag_set(inode, flag))
		return;

	set_inode_flag(inode, flag);
	if (!f2fs_is_volatile_file(inode))
		list_add_tail(&F2FS_I(inode)->dirty_list,
						&sbi->inode_list[type]);
	stat_inc_dirty_inode(sbi, type);
}