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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct TYPE_3__ {struct inode* inode; } ;
struct btrfs_block_group_cache {TYPE_1__ io_ctl; } ;
struct TYPE_4__ {scalar_t__ generation; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  btrfs_put_block_group (struct btrfs_block_group_cache*) ; 
 int /*<<< orphan*/  invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

__attribute__((used)) static void btrfs_cleanup_bg_io(struct btrfs_block_group_cache *cache)
{
	struct inode *inode;

	inode = cache->io_ctl.inode;
	if (inode) {
		invalidate_inode_pages2(inode->i_mapping);
		BTRFS_I(inode)->generation = 0;
		cache->io_ctl.inode = NULL;
		iput(inode);
	}
	btrfs_put_block_group(cache);
}