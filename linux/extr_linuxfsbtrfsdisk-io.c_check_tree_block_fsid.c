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
struct extent_buffer {int dummy; } ;
struct btrfs_fs_info {struct btrfs_fs_devices* fs_devices; } ;
struct btrfs_fs_devices {struct btrfs_fs_devices* seed; int /*<<< orphan*/  fsid; } ;

/* Variables and functions */
 int BTRFS_FSID_SIZE ; 
 int /*<<< orphan*/  btrfs_header_fsid () ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_tree_block_fsid(struct btrfs_fs_info *fs_info,
				 struct extent_buffer *eb)
{
	struct btrfs_fs_devices *fs_devices = fs_info->fs_devices;
	u8 fsid[BTRFS_FSID_SIZE];
	int ret = 1;

	read_extent_buffer(eb, fsid, btrfs_header_fsid(), BTRFS_FSID_SIZE);
	while (fs_devices) {
		if (!memcmp(fsid, fs_devices->fsid, BTRFS_FSID_SIZE)) {
			ret = 0;
			break;
		}
		fs_devices = fs_devices->seed;
	}
	return ret;
}