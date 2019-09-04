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
typedef  enum inode_type { ____Placeholder_inode_type } inode_type ;
struct TYPE_2__ {int /*<<< orphan*/  dirty_list; } ;

/* Variables and functions */
 int DIR_INODE ; 
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int FI_DIRTY_DIR ; 
 int FI_DIRTY_FILE ; 
 int /*<<< orphan*/  clear_inode_flag (struct inode*,int) ; 
 scalar_t__ get_dirty_pages (struct inode*) ; 
 int /*<<< orphan*/  is_inode_flag_set (struct inode*,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat_dec_dirty_inode (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __remove_dirty_inode(struct inode *inode, enum inode_type type)
{
	int flag = (type == DIR_INODE) ? FI_DIRTY_DIR : FI_DIRTY_FILE;

	if (get_dirty_pages(inode) || !is_inode_flag_set(inode, flag))
		return;

	list_del_init(&F2FS_I(inode)->dirty_list);
	clear_inode_flag(inode, flag);
	stat_dec_dirty_inode(F2FS_I_SB(inode), type);
}