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
struct btrfs_fs_info {int /*<<< orphan*/  delayed_workers; } ;
struct btrfs_delayed_root {int dummy; } ;
struct btrfs_async_delayed_work {int nr; int /*<<< orphan*/  work; struct btrfs_delayed_root* delayed_root; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  btrfs_async_run_delayed_root ; 
 int /*<<< orphan*/  btrfs_delayed_meta_helper ; 
 int /*<<< orphan*/  btrfs_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct btrfs_async_delayed_work* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btrfs_wq_run_delayed_node(struct btrfs_delayed_root *delayed_root,
				     struct btrfs_fs_info *fs_info, int nr)
{
	struct btrfs_async_delayed_work *async_work;

	async_work = kmalloc(sizeof(*async_work), GFP_NOFS);
	if (!async_work)
		return -ENOMEM;

	async_work->delayed_root = delayed_root;
	btrfs_init_work(&async_work->work, btrfs_delayed_meta_helper,
			btrfs_async_run_delayed_root, NULL, NULL);
	async_work->nr = nr;

	btrfs_queue_work(fs_info->delayed_workers, &async_work->work);
	return 0;
}