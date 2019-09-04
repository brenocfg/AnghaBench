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
struct f2fs_extent {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  extent_tree; } ;

/* Variables and functions */
 TYPE_1__* F2FS_I (struct inode*) ; 
 int /*<<< orphan*/  FI_NO_EXTENT ; 
 int __f2fs_init_extent_tree (struct inode*,struct f2fs_extent*) ; 
 int /*<<< orphan*/  set_inode_flag (struct inode*,int /*<<< orphan*/ ) ; 

bool f2fs_init_extent_tree(struct inode *inode, struct f2fs_extent *i_ext)
{
	bool ret =  __f2fs_init_extent_tree(inode, i_ext);

	if (!F2FS_I(inode)->extent_tree)
		set_inode_flag(inode, FI_NO_EXTENT);

	return ret;
}