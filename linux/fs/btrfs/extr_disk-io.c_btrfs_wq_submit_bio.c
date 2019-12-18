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
struct btrfs_fs_info {int /*<<< orphan*/  workers; } ;
struct bio {int /*<<< orphan*/  bi_opf; } ;
struct async_submit_bio {int mirror_num; int /*<<< orphan*/  work; scalar_t__ status; int /*<<< orphan*/  bio_offset; int /*<<< orphan*/ * submit_bio_start; struct bio* bio; void* private_data; } ;
typedef  int /*<<< orphan*/  extent_submit_bio_start_t ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  btrfs_init_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_set_work_high_priority (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_worker_helper ; 
 struct async_submit_bio* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ op_is_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_one_async_done ; 
 int /*<<< orphan*/  run_one_async_free ; 
 int /*<<< orphan*/  run_one_async_start ; 

blk_status_t btrfs_wq_submit_bio(struct btrfs_fs_info *fs_info, struct bio *bio,
				 int mirror_num, unsigned long bio_flags,
				 u64 bio_offset, void *private_data,
				 extent_submit_bio_start_t *submit_bio_start)
{
	struct async_submit_bio *async;

	async = kmalloc(sizeof(*async), GFP_NOFS);
	if (!async)
		return BLK_STS_RESOURCE;

	async->private_data = private_data;
	async->bio = bio;
	async->mirror_num = mirror_num;
	async->submit_bio_start = submit_bio_start;

	btrfs_init_work(&async->work, btrfs_worker_helper, run_one_async_start,
			run_one_async_done, run_one_async_free);

	async->bio_offset = bio_offset;

	async->status = 0;

	if (op_is_sync(bio->bi_opf))
		btrfs_set_work_high_priority(&async->work);

	btrfs_queue_work(fs_info->workers, &async->work);
	return 0;
}