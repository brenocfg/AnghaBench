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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_fs_info {int /*<<< orphan*/  extent_workers; int /*<<< orphan*/  tree_root; } ;
struct async_delayed_refs {unsigned long count; int error; int sync; int /*<<< orphan*/  wait; int /*<<< orphan*/  work; int /*<<< orphan*/  transid; int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  btrfs_extent_refs_helper ; 
 int /*<<< orphan*/  btrfs_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delayed_ref_async_start ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct async_delayed_refs*) ; 
 struct async_delayed_refs* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int btrfs_async_run_delayed_refs(struct btrfs_fs_info *fs_info,
				 unsigned long count, u64 transid, int wait)
{
	struct async_delayed_refs *async;
	int ret;

	async = kmalloc(sizeof(*async), GFP_NOFS);
	if (!async)
		return -ENOMEM;

	async->root = fs_info->tree_root;
	async->count = count;
	async->error = 0;
	async->transid = transid;
	if (wait)
		async->sync = 1;
	else
		async->sync = 0;
	init_completion(&async->wait);

	btrfs_init_work(&async->work, btrfs_extent_refs_helper,
			delayed_ref_async_start, NULL, NULL);

	btrfs_queue_work(fs_info->extent_workers, &async->work);

	if (wait) {
		wait_for_completion(&async->wait);
		ret = async->error;
		kfree(async);
		return ret;
	}
	return 0;
}