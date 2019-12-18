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
typedef  int /*<<< orphan*/  u8 ;
struct btrfs_fs_devices {int /*<<< orphan*/  fs_info; int /*<<< orphan*/  fsid_kobj; } ;

/* Variables and functions */
 int BTRFS_UUID_UNPARSED_SIZE ; 
 int /*<<< orphan*/  btrfs_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ kobject_rename (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/  const*) ; 

void btrfs_sysfs_update_sprout_fsid(struct btrfs_fs_devices *fs_devices,
				    const u8 *fsid)
{
	char fsid_buf[BTRFS_UUID_UNPARSED_SIZE];

	/*
	 * Sprouting changes fsid of the mounted filesystem, rename the fsid
	 * directory
	 */
	snprintf(fsid_buf, BTRFS_UUID_UNPARSED_SIZE, "%pU", fsid);
	if (kobject_rename(&fs_devices->fsid_kobj, fsid_buf))
		btrfs_warn(fs_devices->fs_info,
				"sysfs: failed to create fsid for sprout");
}