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
typedef  scalar_t__ u64 ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_device {int /*<<< orphan*/  bdev; } ;
struct btrfs_bio {int mirror_num; TYPE_1__* stripes; } ;
struct TYPE_2__ {scalar_t__ physical; struct btrfs_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_MAP_READ ; 
 int btrfs_map_block (struct btrfs_fs_info*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,struct btrfs_bio**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_put_bbio (struct btrfs_bio*) ; 

__attribute__((used)) static void scrub_remap_extent(struct btrfs_fs_info *fs_info,
			       u64 extent_logical, u64 extent_len,
			       u64 *extent_physical,
			       struct btrfs_device **extent_dev,
			       int *extent_mirror_num)
{
	u64 mapped_length;
	struct btrfs_bio *bbio = NULL;
	int ret;

	mapped_length = extent_len;
	ret = btrfs_map_block(fs_info, BTRFS_MAP_READ, extent_logical,
			      &mapped_length, &bbio, 0);
	if (ret || !bbio || mapped_length < extent_len ||
	    !bbio->stripes[0].dev->bdev) {
		btrfs_put_bbio(bbio);
		return;
	}

	*extent_physical = bbio->stripes[0].physical;
	*extent_mirror_num = bbio->mirror_num;
	*extent_dev = bbio->stripes[0].dev;
	btrfs_put_bbio(bbio);
}