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
struct btrfs_fs_info {int dummy; } ;
struct btrfs_end_io_wq {int metadata; struct bio* bio; scalar_t__ status; struct btrfs_fs_info* info; int /*<<< orphan*/  end_io; struct btrfs_end_io_wq* private; } ;
struct bio {int /*<<< orphan*/  bi_end_io; struct btrfs_end_io_wq* bi_private; } ;
typedef  enum btrfs_wq_endio_type { ____Placeholder_btrfs_wq_endio_type } btrfs_wq_endio_type ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_RESOURCE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  btrfs_end_io_wq_cache ; 
 int /*<<< orphan*/  end_workqueue_bio ; 
 struct btrfs_end_io_wq* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

blk_status_t btrfs_bio_wq_end_io(struct btrfs_fs_info *info, struct bio *bio,
			enum btrfs_wq_endio_type metadata)
{
	struct btrfs_end_io_wq *end_io_wq;

	end_io_wq = kmem_cache_alloc(btrfs_end_io_wq_cache, GFP_NOFS);
	if (!end_io_wq)
		return BLK_STS_RESOURCE;

	end_io_wq->private = bio->bi_private;
	end_io_wq->end_io = bio->bi_end_io;
	end_io_wq->info = info;
	end_io_wq->status = 0;
	end_io_wq->bio = bio;
	end_io_wq->metadata = metadata;

	bio->bi_private = end_io_wq;
	bio->bi_end_io = end_workqueue_bio;
	return 0;
}