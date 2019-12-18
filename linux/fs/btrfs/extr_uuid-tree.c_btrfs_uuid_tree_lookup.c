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
typedef  scalar_t__ u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  fs_info; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {int dummy; } ;
typedef  int /*<<< orphan*/  data ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IS_ALIGNED (scalar_t__,int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct btrfs_path* btrfs_alloc_path () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int) ; 
 scalar_t__ btrfs_item_size_nr (struct extent_buffer*,int) ; 
 int btrfs_search_slot (int /*<<< orphan*/ *,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_uuid_to_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_warn (int /*<<< orphan*/ ,char*,unsigned long) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ *,unsigned long,int) ; 

__attribute__((used)) static int btrfs_uuid_tree_lookup(struct btrfs_root *uuid_root, u8 *uuid,
				  u8 type, u64 subid)
{
	int ret;
	struct btrfs_path *path = NULL;
	struct extent_buffer *eb;
	int slot;
	u32 item_size;
	unsigned long offset;
	struct btrfs_key key;

	if (WARN_ON_ONCE(!uuid_root)) {
		ret = -ENOENT;
		goto out;
	}

	path = btrfs_alloc_path();
	if (!path) {
		ret = -ENOMEM;
		goto out;
	}

	btrfs_uuid_to_key(uuid, type, &key);
	ret = btrfs_search_slot(NULL, uuid_root, &key, path, 0, 0);
	if (ret < 0) {
		goto out;
	} else if (ret > 0) {
		ret = -ENOENT;
		goto out;
	}

	eb = path->nodes[0];
	slot = path->slots[0];
	item_size = btrfs_item_size_nr(eb, slot);
	offset = btrfs_item_ptr_offset(eb, slot);
	ret = -ENOENT;

	if (!IS_ALIGNED(item_size, sizeof(u64))) {
		btrfs_warn(uuid_root->fs_info,
			   "uuid item with illegal size %lu!",
			   (unsigned long)item_size);
		goto out;
	}
	while (item_size) {
		__le64 data;

		read_extent_buffer(eb, &data, offset, sizeof(data));
		if (le64_to_cpu(data) == subid) {
			ret = 0;
			break;
		}
		offset += sizeof(data);
		item_size -= sizeof(data);
	}

out:
	btrfs_free_path(path);
	return ret;
}