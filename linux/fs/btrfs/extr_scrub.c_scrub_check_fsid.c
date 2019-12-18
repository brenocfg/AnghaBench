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
typedef  int /*<<< orphan*/  u8 ;
struct scrub_page {TYPE_1__* dev; } ;
struct btrfs_fs_devices {int /*<<< orphan*/  fsid; } ;
struct TYPE_2__ {struct btrfs_fs_devices* fs_devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FSID_SIZE ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int scrub_check_fsid(u8 fsid[],
				   struct scrub_page *spage)
{
	struct btrfs_fs_devices *fs_devices = spage->dev->fs_devices;
	int ret;

	ret = memcmp(fsid, fs_devices->fsid, BTRFS_FSID_SIZE);
	return !ret;
}