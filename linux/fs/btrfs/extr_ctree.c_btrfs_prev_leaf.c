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
typedef  scalar_t__ u8 ;
typedef  void* u64 ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int /*<<< orphan*/ * nodes; } ;
struct btrfs_key {scalar_t__ offset; scalar_t__ type; scalar_t__ objectid; } ;
struct btrfs_disk_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_item_key (int /*<<< orphan*/ ,struct btrfs_disk_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (int /*<<< orphan*/ ,struct btrfs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int comp_keys (struct btrfs_disk_key*,struct btrfs_key*) ; 

int btrfs_prev_leaf(struct btrfs_root *root, struct btrfs_path *path)
{
	struct btrfs_key key;
	struct btrfs_disk_key found_key;
	int ret;

	btrfs_item_key_to_cpu(path->nodes[0], &key, 0);

	if (key.offset > 0) {
		key.offset--;
	} else if (key.type > 0) {
		key.type--;
		key.offset = (u64)-1;
	} else if (key.objectid > 0) {
		key.objectid--;
		key.type = (u8)-1;
		key.offset = (u64)-1;
	} else {
		return 1;
	}

	btrfs_release_path(path);
	ret = btrfs_search_slot(NULL, root, &key, path, 0, 0);
	if (ret < 0)
		return ret;
	btrfs_item_key(path->nodes[0], &found_key, 0);
	ret = comp_keys(&found_key, &key);
	/*
	 * We might have had an item with the previous key in the tree right
	 * before we released our path. And after we released our path, that
	 * item might have been pushed to the first slot (0) of the leaf we
	 * were holding due to a tree balance. Alternatively, an item with the
	 * previous key can exist as the only element of a leaf (big fat item).
	 * Therefore account for these 2 cases, so that our callers (like
	 * btrfs_previous_item) don't miss an existing item with a key matching
	 * the previous key we computed above.
	 */
	if (ret <= 0)
		return 0;
	return 1;
}