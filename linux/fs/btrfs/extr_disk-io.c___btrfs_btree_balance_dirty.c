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
struct btrfs_fs_info {TYPE_1__* btree_inode; int /*<<< orphan*/  dirty_metadata_batch; int /*<<< orphan*/  dirty_metadata_bytes; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DIRTY_METADATA_THRESH ; 
 int PF_MEMALLOC ; 
 int __percpu_counter_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  balance_dirty_pages_ratelimited (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_balance_delayed_items (struct btrfs_fs_info*) ; 
 TYPE_2__* current ; 

__attribute__((used)) static void __btrfs_btree_balance_dirty(struct btrfs_fs_info *fs_info,
					int flush_delayed)
{
	/*
	 * looks as though older kernels can get into trouble with
	 * this code, they end up stuck in balance_dirty_pages forever
	 */
	int ret;

	if (current->flags & PF_MEMALLOC)
		return;

	if (flush_delayed)
		btrfs_balance_delayed_items(fs_info);

	ret = __percpu_counter_compare(&fs_info->dirty_metadata_bytes,
				     BTRFS_DIRTY_METADATA_THRESH,
				     fs_info->dirty_metadata_batch);
	if (ret > 0) {
		balance_dirty_pages_ratelimited(fs_info->btree_inode->i_mapping);
	}
}