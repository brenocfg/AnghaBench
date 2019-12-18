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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  subid_le ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {struct btrfs_fs_info* fs_info; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ offset; scalar_t__ objectid; } ;
struct btrfs_fs_info {struct btrfs_root* uuid_root; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_extend_item (struct btrfs_path*,int) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 int btrfs_insert_empty_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,int) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int) ; 
 int btrfs_item_size_nr (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_mark_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_uuid_to_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct btrfs_key*) ; 
 int btrfs_uuid_tree_lookup (struct btrfs_root*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_warn (struct btrfs_fs_info*,char*,int,unsigned long long,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ *,unsigned long,int) ; 

int btrfs_uuid_tree_add(struct btrfs_trans_handle *trans, u8 *uuid, u8 type,
			u64 subid_cpu)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_root *uuid_root = fs_info->uuid_root;
	int ret;
	struct btrfs_path *path = NULL;
	struct btrfs_key key;
	struct extent_buffer *eb;
	int slot;
	unsigned long offset;
	__le64 subid_le;

	ret = btrfs_uuid_tree_lookup(uuid_root, uuid, type, subid_cpu);
	if (ret != -ENOENT)
		return ret;

	if (WARN_ON_ONCE(!uuid_root)) {
		ret = -EINVAL;
		goto out;
	}

	btrfs_uuid_to_key(uuid, type, &key);

	path = btrfs_alloc_path();
	if (!path) {
		ret = -ENOMEM;
		goto out;
	}

	ret = btrfs_insert_empty_item(trans, uuid_root, path, &key,
				      sizeof(subid_le));
	if (ret >= 0) {
		/* Add an item for the type for the first time */
		eb = path->nodes[0];
		slot = path->slots[0];
		offset = btrfs_item_ptr_offset(eb, slot);
	} else if (ret == -EEXIST) {
		/*
		 * An item with that type already exists.
		 * Extend the item and store the new subid at the end.
		 */
		btrfs_extend_item(path, sizeof(subid_le));
		eb = path->nodes[0];
		slot = path->slots[0];
		offset = btrfs_item_ptr_offset(eb, slot);
		offset += btrfs_item_size_nr(eb, slot) - sizeof(subid_le);
	} else {
		btrfs_warn(fs_info,
			   "insert uuid item failed %d (0x%016llx, 0x%016llx) type %u!",
			   ret, (unsigned long long)key.objectid,
			   (unsigned long long)key.offset, type);
		goto out;
	}

	ret = 0;
	subid_le = cpu_to_le64(subid_cpu);
	write_extent_buffer(eb, &subid_le, offset, sizeof(subid_le));
	btrfs_mark_buffer_dirty(eb);

out:
	btrfs_free_path(path);
	return ret;
}