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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_key {int /*<<< orphan*/  offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ORPHAN_ITEM_KEY ; 
 int /*<<< orphan*/  BTRFS_ORPHAN_OBJECTID ; 
 int ENOMEM ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int btrfs_insert_empty_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,int /*<<< orphan*/ ) ; 

int btrfs_insert_orphan_item(struct btrfs_trans_handle *trans,
			     struct btrfs_root *root, u64 offset)
{
	struct btrfs_path *path;
	struct btrfs_key key;
	int ret = 0;

	key.objectid = BTRFS_ORPHAN_OBJECTID;
	key.type = BTRFS_ORPHAN_ITEM_KEY;
	key.offset = offset;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	ret = btrfs_insert_empty_item(trans, root, path, &key, 0);

	btrfs_free_path(path);
	return ret;
}