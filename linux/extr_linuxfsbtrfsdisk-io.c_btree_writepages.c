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
struct writeback_control {scalar_t__ sync_mode; scalar_t__ for_kupdate; } ;
struct btrfs_fs_info {int /*<<< orphan*/  dirty_metadata_batch; int /*<<< orphan*/  dirty_metadata_bytes; } ;
struct address_space {int /*<<< orphan*/  host; } ;
struct TYPE_4__ {TYPE_1__* root; } ;
struct TYPE_3__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DIRTY_METADATA_THRESH ; 
 TYPE_2__* BTRFS_I (int /*<<< orphan*/ ) ; 
 scalar_t__ WB_SYNC_NONE ; 
 int __percpu_counter_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btree_write_cache_pages (struct address_space*,struct writeback_control*) ; 

__attribute__((used)) static int btree_writepages(struct address_space *mapping,
			    struct writeback_control *wbc)
{
	struct btrfs_fs_info *fs_info;
	int ret;

	if (wbc->sync_mode == WB_SYNC_NONE) {

		if (wbc->for_kupdate)
			return 0;

		fs_info = BTRFS_I(mapping->host)->root->fs_info;
		/* this is a bit racy, but that's ok */
		ret = __percpu_counter_compare(&fs_info->dirty_metadata_bytes,
					     BTRFS_DIRTY_METADATA_THRESH,
					     fs_info->dirty_metadata_batch);
		if (ret < 0)
			return 0;
	}
	return btree_write_cache_pages(mapping, wbc);
}