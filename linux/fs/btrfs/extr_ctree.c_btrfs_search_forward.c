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
typedef  int u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int keep_locks; int lowest_level; int* slots; struct extent_buffer** nodes; void** locks; } ;
struct btrfs_key {int dummy; } ;
typedef  int /*<<< orphan*/  found_key ;

/* Variables and functions */
 void* BTRFS_READ_LOCK ; 
 scalar_t__ IS_ERR (struct extent_buffer*) ; 
 int PTR_ERR (struct extent_buffer*) ; 
 int /*<<< orphan*/  WARN_ON (struct extent_buffer*) ; 
 int btrfs_bin_search (struct extent_buffer*,struct btrfs_key*,int,int*) ; 
 int btrfs_find_next_key (struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,int,scalar_t__) ; 
 scalar_t__ btrfs_header_generation (struct extent_buffer*) ; 
 int btrfs_header_level (struct extent_buffer*) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 int /*<<< orphan*/  btrfs_node_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 scalar_t__ btrfs_node_ptr_generation (struct extent_buffer*,int) ; 
 struct extent_buffer* btrfs_read_lock_root_node (struct btrfs_root*) ; 
 struct extent_buffer* btrfs_read_node_slot (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_set_path_blocking (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_tree_read_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_unlock_up_safe (struct btrfs_path*,int) ; 
 int /*<<< orphan*/  memcpy (struct btrfs_key*,struct btrfs_key*,int) ; 
 int /*<<< orphan*/  unlock_up (struct btrfs_path*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_search_forward(struct btrfs_root *root, struct btrfs_key *min_key,
			 struct btrfs_path *path,
			 u64 min_trans)
{
	struct extent_buffer *cur;
	struct btrfs_key found_key;
	int slot;
	int sret;
	u32 nritems;
	int level;
	int ret = 1;
	int keep_locks = path->keep_locks;

	path->keep_locks = 1;
again:
	cur = btrfs_read_lock_root_node(root);
	level = btrfs_header_level(cur);
	WARN_ON(path->nodes[level]);
	path->nodes[level] = cur;
	path->locks[level] = BTRFS_READ_LOCK;

	if (btrfs_header_generation(cur) < min_trans) {
		ret = 1;
		goto out;
	}
	while (1) {
		nritems = btrfs_header_nritems(cur);
		level = btrfs_header_level(cur);
		sret = btrfs_bin_search(cur, min_key, level, &slot);
		if (sret < 0) {
			ret = sret;
			goto out;
		}

		/* at the lowest level, we're done, setup the path and exit */
		if (level == path->lowest_level) {
			if (slot >= nritems)
				goto find_next_key;
			ret = 0;
			path->slots[level] = slot;
			btrfs_item_key_to_cpu(cur, &found_key, slot);
			goto out;
		}
		if (sret && slot > 0)
			slot--;
		/*
		 * check this node pointer against the min_trans parameters.
		 * If it is too old, old, skip to the next one.
		 */
		while (slot < nritems) {
			u64 gen;

			gen = btrfs_node_ptr_generation(cur, slot);
			if (gen < min_trans) {
				slot++;
				continue;
			}
			break;
		}
find_next_key:
		/*
		 * we didn't find a candidate key in this node, walk forward
		 * and find another one
		 */
		if (slot >= nritems) {
			path->slots[level] = slot;
			btrfs_set_path_blocking(path);
			sret = btrfs_find_next_key(root, path, min_key, level,
						  min_trans);
			if (sret == 0) {
				btrfs_release_path(path);
				goto again;
			} else {
				goto out;
			}
		}
		/* save our key for returning back */
		btrfs_node_key_to_cpu(cur, &found_key, slot);
		path->slots[level] = slot;
		if (level == path->lowest_level) {
			ret = 0;
			goto out;
		}
		btrfs_set_path_blocking(path);
		cur = btrfs_read_node_slot(cur, slot);
		if (IS_ERR(cur)) {
			ret = PTR_ERR(cur);
			goto out;
		}

		btrfs_tree_read_lock(cur);

		path->locks[level - 1] = BTRFS_READ_LOCK;
		path->nodes[level - 1] = cur;
		unlock_up(path, level, 1, 0, NULL);
	}
out:
	path->keep_locks = keep_locks;
	if (ret == 0) {
		btrfs_unlock_up_safe(path, path->lowest_level + 1);
		btrfs_set_path_blocking(path);
		memcpy(min_key, &found_key, sizeof(found_key));
	}
	return ret;
}