#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {struct btrfs_fs_info* fs_info; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {scalar_t__* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ type; scalar_t__ offset; } ;
struct btrfs_fs_info {scalar_t__ sectorsize; struct btrfs_root* free_space_root; } ;
struct btrfs_free_space_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ offset; scalar_t__ objectid; } ;
struct btrfs_block_group_cache {TYPE_1__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BTRFS_FREE_SPACE_BITMAP_BITS ; 
 scalar_t__ BTRFS_FREE_SPACE_BITMAP_KEY ; 
 scalar_t__ BTRFS_FREE_SPACE_EXTENT_KEY ; 
 scalar_t__ BTRFS_FREE_SPACE_INFO_KEY ; 
 scalar_t__ BTRFS_FREE_SPACE_USING_BITMAPS ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_free_space_info*) ; 
 int PTR_ERR (struct btrfs_free_space_info*) ; 
 unsigned long* alloc_bitmap (scalar_t__) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 int btrfs_del_items (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,scalar_t__,int) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ btrfs_free_space_extent_count (struct extent_buffer*,struct btrfs_free_space_info*) ; 
 scalar_t__ btrfs_free_space_flags (struct extent_buffer*,struct btrfs_free_space_info*) ; 
 int btrfs_insert_empty_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,scalar_t__) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_mark_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_prev_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int,int) ; 
 int /*<<< orphan*/  btrfs_set_free_space_flags (struct extent_buffer*,struct btrfs_free_space_info*,scalar_t__) ; 
 scalar_t__ div_u64 (scalar_t__,scalar_t__) ; 
 scalar_t__ free_space_bitmap_size (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kvfree (unsigned long*) ; 
 int /*<<< orphan*/  le_bitmap_set (unsigned long*,scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 struct btrfs_free_space_info* search_free_space_info (struct btrfs_trans_handle*,struct btrfs_fs_info*,struct btrfs_block_group_cache*,struct btrfs_path*,int) ; 
 int /*<<< orphan*/  write_extent_buffer (struct extent_buffer*,char*,unsigned long,scalar_t__) ; 

int convert_free_space_to_bitmaps(struct btrfs_trans_handle *trans,
				  struct btrfs_block_group_cache *block_group,
				  struct btrfs_path *path)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_root *root = fs_info->free_space_root;
	struct btrfs_free_space_info *info;
	struct btrfs_key key, found_key;
	struct extent_buffer *leaf;
	unsigned long *bitmap;
	char *bitmap_cursor;
	u64 start, end;
	u64 bitmap_range, i;
	u32 bitmap_size, flags, expected_extent_count;
	u32 extent_count = 0;
	int done = 0, nr;
	int ret;

	bitmap_size = free_space_bitmap_size(block_group->key.offset,
					     fs_info->sectorsize);
	bitmap = alloc_bitmap(bitmap_size);
	if (!bitmap) {
		ret = -ENOMEM;
		goto out;
	}

	start = block_group->key.objectid;
	end = block_group->key.objectid + block_group->key.offset;

	key.objectid = end - 1;
	key.type = (u8)-1;
	key.offset = (u64)-1;

	while (!done) {
		ret = btrfs_search_prev_slot(trans, root, &key, path, -1, 1);
		if (ret)
			goto out;

		leaf = path->nodes[0];
		nr = 0;
		path->slots[0]++;
		while (path->slots[0] > 0) {
			btrfs_item_key_to_cpu(leaf, &found_key, path->slots[0] - 1);

			if (found_key.type == BTRFS_FREE_SPACE_INFO_KEY) {
				ASSERT(found_key.objectid == block_group->key.objectid);
				ASSERT(found_key.offset == block_group->key.offset);
				done = 1;
				break;
			} else if (found_key.type == BTRFS_FREE_SPACE_EXTENT_KEY) {
				u64 first, last;

				ASSERT(found_key.objectid >= start);
				ASSERT(found_key.objectid < end);
				ASSERT(found_key.objectid + found_key.offset <= end);

				first = div_u64(found_key.objectid - start,
						fs_info->sectorsize);
				last = div_u64(found_key.objectid + found_key.offset - start,
					       fs_info->sectorsize);
				le_bitmap_set(bitmap, first, last - first);

				extent_count++;
				nr++;
				path->slots[0]--;
			} else {
				ASSERT(0);
			}
		}

		ret = btrfs_del_items(trans, root, path, path->slots[0], nr);
		if (ret)
			goto out;
		btrfs_release_path(path);
	}

	info = search_free_space_info(trans, fs_info, block_group, path, 1);
	if (IS_ERR(info)) {
		ret = PTR_ERR(info);
		goto out;
	}
	leaf = path->nodes[0];
	flags = btrfs_free_space_flags(leaf, info);
	flags |= BTRFS_FREE_SPACE_USING_BITMAPS;
	btrfs_set_free_space_flags(leaf, info, flags);
	expected_extent_count = btrfs_free_space_extent_count(leaf, info);
	btrfs_mark_buffer_dirty(leaf);
	btrfs_release_path(path);

	if (extent_count != expected_extent_count) {
		btrfs_err(fs_info,
			  "incorrect extent count for %llu; counted %u, expected %u",
			  block_group->key.objectid, extent_count,
			  expected_extent_count);
		ASSERT(0);
		ret = -EIO;
		goto out;
	}

	bitmap_cursor = (char *)bitmap;
	bitmap_range = fs_info->sectorsize * BTRFS_FREE_SPACE_BITMAP_BITS;
	i = start;
	while (i < end) {
		unsigned long ptr;
		u64 extent_size;
		u32 data_size;

		extent_size = min(end - i, bitmap_range);
		data_size = free_space_bitmap_size(extent_size,
						   fs_info->sectorsize);

		key.objectid = i;
		key.type = BTRFS_FREE_SPACE_BITMAP_KEY;
		key.offset = extent_size;

		ret = btrfs_insert_empty_item(trans, root, path, &key,
					      data_size);
		if (ret)
			goto out;

		leaf = path->nodes[0];
		ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
		write_extent_buffer(leaf, bitmap_cursor, ptr,
				    data_size);
		btrfs_mark_buffer_dirty(leaf);
		btrfs_release_path(path);

		i += extent_size;
		bitmap_cursor += data_size;
	}

	ret = 0;
out:
	kvfree(bitmap);
	if (ret)
		btrfs_abort_transaction(trans, ret);
	return ret;
}