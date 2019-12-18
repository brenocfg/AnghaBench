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
typedef  int u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  fs_info; } ;
struct btrfs_path {int leave_spinning; int /*<<< orphan*/ * slots; struct extent_buffer** nodes; } ;
struct btrfs_key {int /*<<< orphan*/  offset; int /*<<< orphan*/  type; int /*<<< orphan*/  objectid; } ;
struct btrfs_inode_extref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_INODE_EXTREF_KEY ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EROFS ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int btrfs_del_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_extref_hash (int /*<<< orphan*/ ,char const*,int) ; 
 struct btrfs_inode_extref* btrfs_find_name_in_ext_backref (struct extent_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_handle_fs_error (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_inode_extref_index (struct extent_buffer*,struct btrfs_inode_extref*) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int btrfs_item_size_nr (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int btrfs_search_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int,int) ; 
 int /*<<< orphan*/  btrfs_truncate_item (struct btrfs_path*,int,int) ; 
 int /*<<< orphan*/  memmove_extent_buffer (struct extent_buffer*,unsigned long,unsigned long,int) ; 

__attribute__((used)) static int btrfs_del_inode_extref(struct btrfs_trans_handle *trans,
				  struct btrfs_root *root,
				  const char *name, int name_len,
				  u64 inode_objectid, u64 ref_objectid,
				  u64 *index)
{
	struct btrfs_path *path;
	struct btrfs_key key;
	struct btrfs_inode_extref *extref;
	struct extent_buffer *leaf;
	int ret;
	int del_len = name_len + sizeof(*extref);
	unsigned long ptr;
	unsigned long item_start;
	u32 item_size;

	key.objectid = inode_objectid;
	key.type = BTRFS_INODE_EXTREF_KEY;
	key.offset = btrfs_extref_hash(ref_objectid, name, name_len);

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	path->leave_spinning = 1;

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	if (ret > 0)
		ret = -ENOENT;
	if (ret < 0)
		goto out;

	/*
	 * Sanity check - did we find the right item for this name?
	 * This should always succeed so error here will make the FS
	 * readonly.
	 */
	extref = btrfs_find_name_in_ext_backref(path->nodes[0], path->slots[0],
						ref_objectid, name, name_len);
	if (!extref) {
		btrfs_handle_fs_error(root->fs_info, -ENOENT, NULL);
		ret = -EROFS;
		goto out;
	}

	leaf = path->nodes[0];
	item_size = btrfs_item_size_nr(leaf, path->slots[0]);
	if (index)
		*index = btrfs_inode_extref_index(leaf, extref);

	if (del_len == item_size) {
		/*
		 * Common case only one ref in the item, remove the
		 * whole item.
		 */
		ret = btrfs_del_item(trans, root, path);
		goto out;
	}

	ptr = (unsigned long)extref;
	item_start = btrfs_item_ptr_offset(leaf, path->slots[0]);

	memmove_extent_buffer(leaf, ptr, ptr + del_len,
			      item_size - (ptr + del_len - item_start));

	btrfs_truncate_item(path, item_size - del_len, 1);

out:
	btrfs_free_path(path);

	return ret;
}