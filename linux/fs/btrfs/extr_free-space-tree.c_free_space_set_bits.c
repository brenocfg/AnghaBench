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
struct btrfs_path {int /*<<< orphan*/ * slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ type; scalar_t__ objectid; scalar_t__ offset; } ;
struct btrfs_fs_info {int /*<<< orphan*/  sectorsize; } ;
struct btrfs_block_group_cache {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BTRFS_FREE_SPACE_BITMAP_KEY ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int /*<<< orphan*/ ) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_mark_buffer_dirty (struct extent_buffer*) ; 
 unsigned long div_u64 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_buffer_bitmap_clear (struct extent_buffer*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  extent_buffer_bitmap_set (struct extent_buffer*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static void free_space_set_bits(struct btrfs_block_group_cache *block_group,
				struct btrfs_path *path, u64 *start, u64 *size,
				int bit)
{
	struct btrfs_fs_info *fs_info = block_group->fs_info;
	struct extent_buffer *leaf;
	struct btrfs_key key;
	u64 end = *start + *size;
	u64 found_start, found_end;
	unsigned long ptr, first, last;

	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
	ASSERT(key.type == BTRFS_FREE_SPACE_BITMAP_KEY);

	found_start = key.objectid;
	found_end = key.objectid + key.offset;
	ASSERT(*start >= found_start && *start < found_end);
	ASSERT(end > found_start);

	if (end > found_end)
		end = found_end;

	ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
	first = div_u64(*start - found_start, fs_info->sectorsize);
	last = div_u64(end - found_start, fs_info->sectorsize);
	if (bit)
		extent_buffer_bitmap_set(leaf, ptr, first, last - first);
	else
		extent_buffer_bitmap_clear(leaf, ptr, first, last - first);
	btrfs_mark_buffer_dirty(leaf);

	*size -= end - *start;
	*start = end;
}