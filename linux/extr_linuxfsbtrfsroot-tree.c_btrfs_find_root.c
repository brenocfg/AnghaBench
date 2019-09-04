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
struct extent_buffer {int dummy; } ;
struct btrfs_root_item {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {unsigned long long offset; scalar_t__ objectid; scalar_t__ type; } ;
typedef  int /*<<< orphan*/  found_key ;

/* Variables and functions */
 scalar_t__ BTRFS_ROOT_ITEM_KEY ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 int /*<<< orphan*/  btrfs_read_root_item (struct extent_buffer*,int,struct btrfs_root_item*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key const*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct btrfs_key*,struct btrfs_key*,int) ; 

int btrfs_find_root(struct btrfs_root *root, const struct btrfs_key *search_key,
		    struct btrfs_path *path, struct btrfs_root_item *root_item,
		    struct btrfs_key *root_key)
{
	struct btrfs_key found_key;
	struct extent_buffer *l;
	int ret;
	int slot;

	ret = btrfs_search_slot(NULL, root, search_key, path, 0, 0);
	if (ret < 0)
		return ret;

	if (search_key->offset != -1ULL) {	/* the search key is exact */
		if (ret > 0)
			goto out;
	} else {
		BUG_ON(ret == 0);		/* Logical error */
		if (path->slots[0] == 0)
			goto out;
		path->slots[0]--;
		ret = 0;
	}

	l = path->nodes[0];
	slot = path->slots[0];

	btrfs_item_key_to_cpu(l, &found_key, slot);
	if (found_key.objectid != search_key->objectid ||
	    found_key.type != BTRFS_ROOT_ITEM_KEY) {
		ret = 1;
		goto out;
	}

	if (root_item)
		btrfs_read_root_item(l, slot, root_item);
	if (root_key)
		memcpy(root_key, &found_key, sizeof(found_key));
out:
	btrfs_release_path(path);
	return ret;
}