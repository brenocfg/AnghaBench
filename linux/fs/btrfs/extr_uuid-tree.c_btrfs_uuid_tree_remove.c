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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  subid ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {struct btrfs_fs_info* fs_info; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_fs_info {struct btrfs_root* uuid_root; } ;
typedef  int /*<<< orphan*/  read_subid ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ALIGNED (int,int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int btrfs_del_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int) ; 
 int btrfs_item_size_nr (struct extent_buffer*,int) ; 
 int btrfs_search_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int,int) ; 
 int /*<<< orphan*/  btrfs_truncate_item (struct btrfs_path*,int,int) ; 
 int /*<<< orphan*/  btrfs_uuid_to_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_warn (struct btrfs_fs_info*,char*,unsigned long) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove_extent_buffer (struct extent_buffer*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ *,unsigned long,int) ; 

int btrfs_uuid_tree_remove(struct btrfs_trans_handle *trans, u8 *uuid, u8 type,
			u64 subid)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_root *uuid_root = fs_info->uuid_root;
	int ret;
	struct btrfs_path *path = NULL;
	struct btrfs_key key;
	struct extent_buffer *eb;
	int slot;
	unsigned long offset;
	u32 item_size;
	unsigned long move_dst;
	unsigned long move_src;
	unsigned long move_len;

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

	ret = btrfs_search_slot(trans, uuid_root, &key, path, -1, 1);
	if (ret < 0) {
		btrfs_warn(fs_info, "error %d while searching for uuid item!",
			   ret);
		goto out;
	}
	if (ret > 0) {
		ret = -ENOENT;
		goto out;
	}

	eb = path->nodes[0];
	slot = path->slots[0];
	offset = btrfs_item_ptr_offset(eb, slot);
	item_size = btrfs_item_size_nr(eb, slot);
	if (!IS_ALIGNED(item_size, sizeof(u64))) {
		btrfs_warn(fs_info, "uuid item with illegal size %lu!",
			   (unsigned long)item_size);
		ret = -ENOENT;
		goto out;
	}
	while (item_size) {
		__le64 read_subid;

		read_extent_buffer(eb, &read_subid, offset, sizeof(read_subid));
		if (le64_to_cpu(read_subid) == subid)
			break;
		offset += sizeof(read_subid);
		item_size -= sizeof(read_subid);
	}

	if (!item_size) {
		ret = -ENOENT;
		goto out;
	}

	item_size = btrfs_item_size_nr(eb, slot);
	if (item_size == sizeof(subid)) {
		ret = btrfs_del_item(trans, uuid_root, path);
		goto out;
	}

	move_dst = offset;
	move_src = offset + sizeof(subid);
	move_len = item_size - (move_src - btrfs_item_ptr_offset(eb, slot));
	memmove_extent_buffer(eb, move_dst, move_src, move_len);
	btrfs_truncate_item(path, item_size - sizeof(subid), 1);

out:
	btrfs_free_path(path);
	return ret;
}