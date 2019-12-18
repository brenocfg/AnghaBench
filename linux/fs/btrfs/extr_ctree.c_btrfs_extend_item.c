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
typedef  scalar_t__ u32 ;
struct extent_buffer {int /*<<< orphan*/  fs_info; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;
struct btrfs_map_token {int dummy; } ;
struct btrfs_item {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFS_LEAF_DATA_OFFSET ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  btrfs_crit (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 scalar_t__ btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_init_map_token (struct btrfs_map_token*,struct extent_buffer*) ; 
 unsigned int btrfs_item_end_nr (struct extent_buffer*,int) ; 
 struct btrfs_item* btrfs_item_nr (int) ; 
 unsigned int btrfs_item_size_nr (struct extent_buffer*,int) ; 
 scalar_t__ btrfs_leaf_free_space (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_mark_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_print_leaf (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_item_size (struct extent_buffer*,struct btrfs_item*,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_set_token_item_offset (struct extent_buffer*,struct btrfs_item*,scalar_t__,struct btrfs_map_token*) ; 
 scalar_t__ btrfs_token_item_offset (struct extent_buffer*,struct btrfs_item*,struct btrfs_map_token*) ; 
 unsigned int leaf_data_end (struct extent_buffer*) ; 
 int /*<<< orphan*/  memmove_extent_buffer (struct extent_buffer*,scalar_t__,scalar_t__,unsigned int) ; 

void btrfs_extend_item(struct btrfs_path *path, u32 data_size)
{
	int slot;
	struct extent_buffer *leaf;
	struct btrfs_item *item;
	u32 nritems;
	unsigned int data_end;
	unsigned int old_data;
	unsigned int old_size;
	int i;
	struct btrfs_map_token token;

	leaf = path->nodes[0];

	nritems = btrfs_header_nritems(leaf);
	data_end = leaf_data_end(leaf);

	if (btrfs_leaf_free_space(leaf) < data_size) {
		btrfs_print_leaf(leaf);
		BUG();
	}
	slot = path->slots[0];
	old_data = btrfs_item_end_nr(leaf, slot);

	BUG_ON(slot < 0);
	if (slot >= nritems) {
		btrfs_print_leaf(leaf);
		btrfs_crit(leaf->fs_info, "slot %d too large, nritems %d",
			   slot, nritems);
		BUG();
	}

	/*
	 * item0..itemN ... dataN.offset..dataN.size .. data0.size
	 */
	/* first correct the data pointers */
	btrfs_init_map_token(&token, leaf);
	for (i = slot; i < nritems; i++) {
		u32 ioff;
		item = btrfs_item_nr(i);

		ioff = btrfs_token_item_offset(leaf, item, &token);
		btrfs_set_token_item_offset(leaf, item,
					    ioff - data_size, &token);
	}

	/* shift the data */
	memmove_extent_buffer(leaf, BTRFS_LEAF_DATA_OFFSET +
		      data_end - data_size, BTRFS_LEAF_DATA_OFFSET +
		      data_end, old_data - data_end);

	data_end = old_data;
	old_size = btrfs_item_size_nr(leaf, slot);
	item = btrfs_item_nr(slot);
	btrfs_set_item_size(leaf, item, old_size + data_size);
	btrfs_mark_buffer_dirty(leaf);

	if (btrfs_leaf_free_space(leaf) < 0) {
		btrfs_print_leaf(leaf);
		BUG();
	}
}