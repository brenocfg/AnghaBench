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
struct scrub_bio {int /*<<< orphan*/  work; struct bio* bio; int /*<<< orphan*/  status; TYPE_1__* dev; } ;
struct btrfs_fs_info {int /*<<< orphan*/  scrub_workers; } ;
struct bio {int /*<<< orphan*/  bi_status; struct scrub_bio* bi_private; } ;
struct TYPE_2__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scrub_bio_end_io(struct bio *bio)
{
	struct scrub_bio *sbio = bio->bi_private;
	struct btrfs_fs_info *fs_info = sbio->dev->fs_info;

	sbio->status = bio->bi_status;
	sbio->bio = bio;

	btrfs_queue_work(fs_info->scrub_workers, &sbio->work);
}