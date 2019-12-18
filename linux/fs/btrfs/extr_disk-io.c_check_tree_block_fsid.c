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
struct extent_buffer {struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {struct btrfs_fs_devices* fs_devices; } ;
struct btrfs_fs_devices {struct btrfs_fs_devices* seed; int /*<<< orphan*/ * fsid; int /*<<< orphan*/ * metadata_uuid; } ;

/* Variables and functions */
 int BTRFS_FSID_SIZE ; 
 int /*<<< orphan*/  METADATA_UUID ; 
 scalar_t__ btrfs_fs_incompat (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_header_fsid () ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_tree_block_fsid(struct extent_buffer *eb)
{
	struct btrfs_fs_info *fs_info = eb->fs_info;
	struct btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	u8 fsid[BTRFS_FSID_SIZE];
	int ret = 1;

	read_extent_buffer(eb, fsid, btrfs_header_fsid(), BTRFS_FSID_SIZE);
	while (fs_devices) {
		u8 *metadata_uuid;

		/*
		 * Checking the incompat flag is only valid for the current
		 * fs. For seed devices it's forbidden to have their uuid
		 * changed so reading ->fsid in this case is fine
		 */
		if (fs_devices == fs_info->fs_devices &&
		    btrfs_fs_incompat(fs_info, METADATA_UUID))
			metadata_uuid = fs_devices->metadata_uuid;
		else
			metadata_uuid = fs_devices->fsid;

		if (!memcmp(fsid, metadata_uuid, BTRFS_FSID_SIZE)) {
			ret = 0;
			break;
		}
		fs_devices = fs_devices->seed;
	}
	return ret;
}