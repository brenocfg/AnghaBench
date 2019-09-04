#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_3__ {scalar_t__ len; } ;
struct extent_tree {int /*<<< orphan*/  lock; TYPE_1__ largest; } ;
struct TYPE_4__ {struct extent_tree* extent_tree; } ;

/* Variables and functions */
 TYPE_2__* F2FS_I (struct inode*) ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  FI_NO_EXTENT ; 
 int /*<<< orphan*/  __free_extent_tree (struct f2fs_sb_info*,struct extent_tree*) ; 
 int /*<<< orphan*/  f2fs_mark_inode_dirty_sync (struct inode*,int) ; 
 int /*<<< orphan*/  f2fs_may_extent_tree (struct inode*) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void f2fs_drop_extent_tree(struct inode *inode)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);
	struct extent_tree *et = F2FS_I(inode)->extent_tree;
	bool updated = false;

	if (!f2fs_may_extent_tree(inode))
		return;

	set_inode_flag(inode, FI_NO_EXTENT);

	write_lock(&et->lock);
	__free_extent_tree(sbi, et);
	if (et->largest.len) {
		et->largest.len = 0;
		updated = true;
	}
	write_unlock(&et->lock);
	if (updated)
		f2fs_mark_inode_dirty_sync(inode, true);
}