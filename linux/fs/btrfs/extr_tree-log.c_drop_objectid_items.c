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
typedef  scalar_t__ u64 ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int* slots; int /*<<< orphan*/ * nodes; } ;
struct btrfs_key {scalar_t__ objectid; int type; scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int btrfs_bin_search (int /*<<< orphan*/ ,struct btrfs_key*,int /*<<< orphan*/ ,int*) ; 
 int btrfs_del_items (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,int,int) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (int /*<<< orphan*/ ,struct btrfs_key*,int) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int,int) ; 

__attribute__((used)) static int drop_objectid_items(struct btrfs_trans_handle *trans,
				  struct btrfs_root *log,
				  struct btrfs_path *path,
				  u64 objectid, int max_key_type)
{
	int ret;
	struct btrfs_key key;
	struct btrfs_key found_key;
	int start_slot;

	key.objectid = objectid;
	key.type = max_key_type;
	key.offset = (u64)-1;

	while (1) {
		ret = btrfs_search_slot(trans, log, &key, path, -1, 1);
		BUG_ON(ret == 0); /* Logic error */
		if (ret < 0)
			break;

		if (path->slots[0] == 0)
			break;

		path->slots[0]--;
		btrfs_item_key_to_cpu(path->nodes[0], &found_key,
				      path->slots[0]);

		if (found_key.objectid != objectid)
			break;

		found_key.offset = 0;
		found_key.type = 0;
		ret = btrfs_bin_search(path->nodes[0], &found_key, 0,
				       &start_slot);
		if (ret < 0)
			break;

		ret = btrfs_del_items(trans, log, path, start_slot,
				      path->slots[0] - start_slot + 1);
		/*
		 * If start slot isn't 0 then we don't need to re-search, we've
		 * found the last guy with the objectid in this tree.
		 */
		if (ret || start_slot != 0)
			break;
		btrfs_release_path(path);
	}
	btrfs_release_path(path);
	if (ret > 0)
		ret = 0;
	return ret;
}