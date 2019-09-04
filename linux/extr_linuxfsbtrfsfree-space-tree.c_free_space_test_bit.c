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
typedef  scalar_t__ u64 ;
struct extent_buffer {int dummy; } ;
struct btrfs_path {int /*<<< orphan*/ * slots; struct extent_buffer** nodes; } ;
struct btrfs_key {scalar_t__ type; scalar_t__ objectid; scalar_t__ offset; } ;
struct btrfs_block_group_cache {TYPE_1__* fs_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  sectorsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BTRFS_FREE_SPACE_BITMAP_KEY ; 
 int /*<<< orphan*/  btrfs_item_key_to_cpu (struct extent_buffer*,struct btrfs_key*,int /*<<< orphan*/ ) ; 
 unsigned long btrfs_item_ptr_offset (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 unsigned long div_u64 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extent_buffer_test_bit (struct extent_buffer*,unsigned long,unsigned long) ; 

int free_space_test_bit(struct btrfs_block_group_cache *block_group,
			struct btrfs_path *path, u64 offset)
{
	struct extent_buffer *leaf;
	struct btrfs_key key;
	u64 found_start, found_end;
	unsigned long ptr, i;

	leaf = path->nodes[0];
	btrfs_item_key_to_cpu(leaf, &key, path->slots[0]);
	ASSERT(key.type == BTRFS_FREE_SPACE_BITMAP_KEY);

	found_start = key.objectid;
	found_end = key.objectid + key.offset;
	ASSERT(offset >= found_start && offset < found_end);

	ptr = btrfs_item_ptr_offset(leaf, path->slots[0]);
	i = div_u64(offset - found_start,
		    block_group->fs_info->sectorsize);
	return !!extent_buffer_test_bit(leaf, ptr, i);
}