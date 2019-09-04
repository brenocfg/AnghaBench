#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {struct btrfs_fs_info* fs_info; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {scalar_t__* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ type; scalar_t__ offset; } ;
struct btrfs_fs_info {int sectorsize; struct btrfs_root* free_space_root; } ;
struct btrfs_free_space_info {int dummy; } ;
struct TYPE_4__ {scalar_t__ offset; scalar_t__ objectid; } ;
struct btrfs_block_group_cache {TYPE_2__ key; TYPE_1__* fs_info; } ;
struct TYPE_3__ {int sectorsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BITS_PER_BYTE ; 
 scalar_t__ BTRFS_FREE_SPACE_BITMAP_KEY ; 
 scalar_t__ BTRFS_FREE_SPACE_EXTENT_KEY ; 
 scalar_t__ BTRFS_FREE_SPACE_INFO_KEY ; 
 int BTRFS_FREE_SPACE_USING_BITMAPS ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_free_space_info*) ; 
 int PTR_ERR (struct btrfs_free_space_info*) ; 
 unsigned long* alloc_bitmap (int) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,int) ; 
 int btrfs_del_items (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,scalar_t__,int) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,scalar_t__,int,int) ; 
 int btrfs_free_space_extent_count (struct extent_buffer*,struct btrfs_free_space_info*) ; 
 int btrfs_free_space_flags (struct extent_buffer*,struct btrfs_free_space_info*) ; 
 int btrfs_insert_empty_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct btrfs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,scalar_t__) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_mark_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int btrfs_search_prev_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int,int) ; 
 int /*<<< orphan*/  btrfs_set_free_space_flags (struct extent_buffer*,struct btrfs_free_space_info*,int) ; 
 void* div_u64 (scalar_t__,int) ; 
 unsigned long find_next_bit_le (unsigned long*,unsigned long,unsigned long) ; 
 unsigned long find_next_zero_bit_le (unsigned long*,unsigned long,unsigned long) ; 
 int free_space_bitmap_size (scalar_t__,int) ; 
 int /*<<< orphan*/  kvfree (unsigned long*) ; 
 int /*<<< orphan*/  read_extent_buffer (struct extent_buffer*,char*,unsigned long,int) ; 
 struct btrfs_free_space_info* search_free_space_info (struct btrfs_trans_handle*,struct btrfs_fs_info*,struct btrfs_block_group_cache*,struct btrfs_path*,int) ; 

int convert_free_space_to_extents(struct btrfs_trans_handle *trans,
				  struct btrfs_block_group_cache *block_group,
				  struct btrfs_path *path)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_root *root = fs_info->free_space_root;
	struct btrfs_free_space_info *info;
	struct btrfs_key key, found_key;
	struct extent_buffer *leaf;
	unsigned long *bitmap;
	u64 start, end;
	u32 bitmap_size, flags, expected_extent_count;
	unsigned long nrbits, start_bit, end_bit;
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
			} else if (found_key.type == BTRFS_FREE_SPACE_BITMAP_KEY) {
				unsigned long ptr;
				char *bitmap_cursor;
				u32 bitmap_pos, data_size;

				ASSERT(found_key.objectid >= start);
				ASSERT(found_key.objectid < end);
				ASSERT(found_key.objectid + found_key.offset <= end);

				bitmap_pos = div_u64(found_key.objectid - start,
						     fs_info->sectorsize *
						     BITS_PER_BYTE);
				bitmap_cursor = ((char *)bitmap) + bitmap_pos;
				data_size = free_space_bitmap_size(found_key.offset,
								   fs_info->sectorsize);

				ptr = btrfs_item_ptr_offset(leaf, path->slots[0] - 1);
				read_extent_buffer(leaf, bitmap_cursor, ptr,
						   data_size);

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
	flags &= ~BTRFS_FREE_SPACE_USING_BITMAPS;
	btrfs_set_free_space_flags(leaf, info, flags);
	expected_extent_count = btrfs_free_space_extent_count(leaf, info);
	btrfs_mark_buffer_dirty(leaf);
	btrfs_release_path(path);

	nrbits = div_u64(block_group->key.offset, block_group->fs_info->sectorsize);
	start_bit = find_next_bit_le(bitmap, nrbits, 0);

	while (start_bit < nrbits) {
		end_bit = find_next_zero_bit_le(bitmap, nrbits, start_bit);
		ASSERT(start_bit < end_bit);

		key.objectid = start + start_bit * block_group->fs_info->sectorsize;
		key.type = BTRFS_FREE_SPACE_EXTENT_KEY;
		key.offset = (end_bit - start_bit) * block_group->fs_info->sectorsize;

		ret = btrfs_insert_empty_item(trans, root, path, &key, 0);
		if (ret)
			goto out;
		btrfs_release_path(path);

		extent_count++;

		start_bit = find_next_bit_le(bitmap, nrbits, end_bit);
	}

	if (extent_count != expected_extent_count) {
		btrfs_err(fs_info,
			  "incorrect extent count for %llu; counted %u, expected %u",
			  block_group->key.objectid, extent_count,
			  expected_extent_count);
		ASSERT(0);
		ret = -EIO;
		goto out;
	}

	ret = 0;
out:
	kvfree(bitmap);
	if (ret)
		btrfs_abort_transaction(trans, ret);
	return ret;
}