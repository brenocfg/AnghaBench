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
typedef  int u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int leave_spinning; int /*<<< orphan*/ * slots; struct extent_buffer** nodes; } ;
struct btrfs_key {int /*<<< orphan*/  type; void* offset; void* objectid; } ;
struct btrfs_inode_ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_INODE_REF_KEY ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int btrfs_del_inode_extref (struct btrfs_trans_handle*,struct btrfs_root*,char const*,int,void*,void*,void**) ; 
 int btrfs_del_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*) ; 
 struct btrfs_inode_ref* btrfs_find_name_in_backref (struct extent_buffer*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 void* btrfs_inode_ref_index (struct extent_buffer*,struct btrfs_inode_ref*) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int btrfs_item_size_nr (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int btrfs_search_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int,int) ; 
 int /*<<< orphan*/  btrfs_truncate_item (struct btrfs_path*,int,int) ; 
 int /*<<< orphan*/  memmove_extent_buffer (struct extent_buffer*,unsigned long,unsigned long,unsigned long) ; 

int btrfs_del_inode_ref(struct btrfs_trans_handle *trans,
			struct btrfs_root *root,
			const char *name, int name_len,
			u64 inode_objectid, u64 ref_objectid, u64 *index)
{
	struct btrfs_path *path;
	struct btrfs_key key;
	struct btrfs_inode_ref *ref;
	struct extent_buffer *leaf;
	unsigned long ptr;
	unsigned long item_start;
	u32 item_size;
	u32 sub_item_len;
	int ret;
	int search_ext_refs = 0;
	int del_len = name_len + sizeof(*ref);

	key.objectid = inode_objectid;
	key.offset = ref_objectid;
	key.type = BTRFS_INODE_REF_KEY;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	path->leave_spinning = 1;

	ret = btrfs_search_slot(trans, root, &key, path, -1, 1);
	if (ret > 0) {
		ret = -ENOENT;
		search_ext_refs = 1;
		goto out;
	} else if (ret < 0) {
		goto out;
	}

	ref = btrfs_find_name_in_backref(path->nodes[0], path->slots[0], name,
					 name_len);
	if (!ref) {
		ret = -ENOENT;
		search_ext_refs = 1;
		goto out;
	}
	leaf = path->nodes[0];
	item_size = btrfs_item_size_nr(leaf, path->slots[0]);

	if (index)
		*index = btrfs_inode_ref_index(leaf, ref);

	if (del_len == item_size) {
		ret = btrfs_del_item(trans, root, path);
		goto out;
	}
	ptr = (unsigned long)ref;
	sub_item_len = name_len + sizeof(*ref);
	item_start = btrfs_item_ptr_offset(leaf, path->slots[0]);
	memmove_extent_buffer(leaf, ptr, ptr + sub_item_len,
			      item_size - (ptr + sub_item_len - item_start));
	btrfs_truncate_item(path, item_size - sub_item_len, 1);
out:
	btrfs_free_path(path);

	if (search_ext_refs) {
		/*
		 * No refs were found, or we could not find the
		 * name in our ref array. Find and remove the extended
		 * inode ref then.
		 */
		return btrfs_del_inode_extref(trans, root, name, name_len,
					      inode_objectid, ref_objectid, index);
	}

	return ret;
}