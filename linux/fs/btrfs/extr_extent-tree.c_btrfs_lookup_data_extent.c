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
struct btrfs_path {int dummy; } ;
struct btrfs_key {int /*<<< orphan*/  type; void* offset; void* objectid; } ;
struct btrfs_fs_info {int /*<<< orphan*/  extent_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_EXTENT_ITEM_KEY ; 
 int ENOMEM ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int btrfs_lookup_data_extent(struct btrfs_fs_info *fs_info, u64 start, u64 len)
{
	int ret;
	struct btrfs_key key;
	struct btrfs_path *path;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	key.objectid = start;
	key.offset = len;
	key.type = BTRFS_EXTENT_ITEM_KEY;
	ret = btrfs_search_slot(NULL, fs_info->extent_root, &key, path, 0, 0);
	btrfs_free_path(path);
	return ret;
}