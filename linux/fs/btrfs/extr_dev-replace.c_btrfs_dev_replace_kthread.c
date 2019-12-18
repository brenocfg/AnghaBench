#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct btrfs_dev_replace {int /*<<< orphan*/  scrub_progress; TYPE_1__* srcdev; int /*<<< orphan*/  committed_cursor_left; TYPE_1__* tgtdev; } ;
struct btrfs_fs_info {int /*<<< orphan*/  flags; struct btrfs_dev_replace dev_replace; } ;
struct TYPE_3__ {int /*<<< orphan*/  devid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_EXCL_OP ; 
 int ECANCELED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  btrfs_dev_name (TYPE_1__*) ; 
 int btrfs_dev_replace_finishing (struct btrfs_fs_info*,int) ; 
 scalar_t__ btrfs_dev_replace_progress (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_device_get_total_bytes (TYPE_1__*) ; 
 int /*<<< orphan*/  btrfs_info_in_rcu (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int btrfs_scrub_dev (struct btrfs_fs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ div_u64 (scalar_t__,int) ; 

__attribute__((used)) static int btrfs_dev_replace_kthread(void *data)
{
	struct btrfs_fs_info *fs_info = data;
	struct btrfs_dev_replace *dev_replace = &fs_info->dev_replace;
	u64 progress;
	int ret;

	progress = btrfs_dev_replace_progress(fs_info);
	progress = div_u64(progress, 10);
	btrfs_info_in_rcu(fs_info,
		"continuing dev_replace from %s (devid %llu) to target %s @%u%%",
		btrfs_dev_name(dev_replace->srcdev),
		dev_replace->srcdev->devid,
		btrfs_dev_name(dev_replace->tgtdev),
		(unsigned int)progress);

	ret = btrfs_scrub_dev(fs_info, dev_replace->srcdev->devid,
			      dev_replace->committed_cursor_left,
			      btrfs_device_get_total_bytes(dev_replace->srcdev),
			      &dev_replace->scrub_progress, 0, 1);
	ret = btrfs_dev_replace_finishing(fs_info, ret);
	WARN_ON(ret && ret != -ECANCELED);

	clear_bit(BTRFS_FS_EXCL_OP, &fs_info->flags);
	return 0;
}