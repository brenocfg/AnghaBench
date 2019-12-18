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
typedef  scalar_t__ u16 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct hfs_find_data {int dummy; } ;
struct TYPE_4__ {scalar_t__ cached_blocks; scalar_t__ cached_start; } ;
struct TYPE_3__ {int /*<<< orphan*/  ext_tree; } ;

/* Variables and functions */
 TYPE_2__* HFS_I (struct inode*) ; 
 TYPE_1__* HFS_SB (int /*<<< orphan*/ ) ; 
 int __hfs_ext_cache_extent (struct hfs_find_data*,struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 

__attribute__((used)) static int hfs_ext_read_extent(struct inode *inode, u16 block)
{
	struct hfs_find_data fd;
	int res;

	if (block >= HFS_I(inode)->cached_start &&
	    block < HFS_I(inode)->cached_start + HFS_I(inode)->cached_blocks)
		return 0;

	res = hfs_find_init(HFS_SB(inode->i_sb)->ext_tree, &fd);
	if (!res) {
		res = __hfs_ext_cache_extent(&fd, inode, block);
		hfs_find_exit(&fd);
	}
	return res;
}