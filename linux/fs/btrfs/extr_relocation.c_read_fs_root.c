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
typedef  void* u64 ;
struct btrfs_root {int dummy; } ;
struct btrfs_key {void* offset; int /*<<< orphan*/  type; void* objectid; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ROOT_ITEM_KEY ; 
 struct btrfs_root* btrfs_get_fs_root (struct btrfs_fs_info*,struct btrfs_key*,int) ; 
 scalar_t__ is_cowonly_root (void*) ; 

__attribute__((used)) static struct btrfs_root *read_fs_root(struct btrfs_fs_info *fs_info,
					u64 root_objectid)
{
	struct btrfs_key key;

	key.objectid = root_objectid;
	key.type = BTRFS_ROOT_ITEM_KEY;
	if (is_cowonly_root(root_objectid))
		key.offset = 0;
	else
		key.offset = (u64)-1;

	return btrfs_get_fs_root(fs_info, &key, false);
}