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
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  log_root; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ type; scalar_t__ offset; } ;
struct btrfs_inode {int flags; int /*<<< orphan*/  vfs_inode; struct btrfs_root* root; } ;

/* Variables and functions */
 scalar_t__ BTRFS_EXTENT_DATA_KEY ; 
 int BTRFS_INODE_PREALLOC ; 
 int EAGAIN ; 
 int ENOMEM ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 scalar_t__ btrfs_ino (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int) ; 
 int btrfs_next_leaf (struct btrfs_root*,struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_truncate_inode_items (struct btrfs_trans_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__ const,scalar_t__) ; 
 int copy_items (struct btrfs_trans_handle*,struct btrfs_inode*,struct btrfs_path*,struct btrfs_path*,scalar_t__*,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_log_prealloc_extents(struct btrfs_trans_handle *trans,
				      struct btrfs_inode *inode,
				      struct btrfs_path *path)
{
	struct btrfs_root *root = inode->root;
	struct btrfs_key key;
	const u64 i_size = i_size_read(&inode->vfs_inode);
	const u64 ino = btrfs_ino(inode);
	struct btrfs_path *dst_path = NULL;
	u64 last_extent = (u64)-1;
	int ins_nr = 0;
	int start_slot;
	int ret;

	if (!(inode->flags & BTRFS_INODE_PREALLOC))
		return 0;

	key.objectid = ino;
	key.type = BTRFS_EXTENT_DATA_KEY;
	key.offset = i_size;
	ret = btrfs_search_slot(NULL, root, &key, path, 0, 0);
	if (ret < 0)
		goto out;

	while (true) {
		struct extent_buffer *leaf = path->nodes[0];
		int slot = path->slots[0];

		if (slot >= btrfs_header_nritems(leaf)) {
			if (ins_nr > 0) {
				ret = copy_items(trans, inode, dst_path, path,
						 &last_extent, start_slot,
						 ins_nr, 1, 0);
				if (ret < 0)
					goto out;
				ins_nr = 0;
			}
			ret = btrfs_next_leaf(root, path);
			if (ret < 0)
				goto out;
			if (ret > 0) {
				ret = 0;
				break;
			}
			continue;
		}

		btrfs_item_key_to_cpu(leaf, &key, slot);
		if (key.objectid > ino)
			break;
		if (WARN_ON_ONCE(key.objectid < ino) ||
		    key.type < BTRFS_EXTENT_DATA_KEY ||
		    key.offset < i_size) {
			path->slots[0]++;
			continue;
		}
		if (last_extent == (u64)-1) {
			last_extent = key.offset;
			/*
			 * Avoid logging extent items logged in past fsync calls
			 * and leading to duplicate keys in the log tree.
			 */
			do {
				ret = btrfs_truncate_inode_items(trans,
							 root->log_root,
							 &inode->vfs_inode,
							 i_size,
							 BTRFS_EXTENT_DATA_KEY);
			} while (ret == -EAGAIN);
			if (ret)
				goto out;
		}
		if (ins_nr == 0)
			start_slot = slot;
		ins_nr++;
		path->slots[0]++;
		if (!dst_path) {
			dst_path = btrfs_alloc_path();
			if (!dst_path) {
				ret = -ENOMEM;
				goto out;
			}
		}
	}
	if (ins_nr > 0) {
		ret = copy_items(trans, inode, dst_path, path, &last_extent,
				 start_slot, ins_nr, 1, 0);
		if (ret > 0)
			ret = 0;
	}
out:
	btrfs_release_path(path);
	btrfs_free_path(dst_path);
	return ret;
}