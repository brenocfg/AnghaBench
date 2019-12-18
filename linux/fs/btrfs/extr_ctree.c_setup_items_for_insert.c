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
typedef  int u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;
struct btrfs_map_token {int dummy; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_item {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_disk_key {int dummy; } ;

/* Variables and functions */
 int BTRFS_LEAF_DATA_OFFSET ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  btrfs_cpu_key_to_disk (struct btrfs_disk_key*,struct btrfs_key const*) ; 
 int /*<<< orphan*/  btrfs_crit (struct btrfs_fs_info*,char*,int,unsigned int,...) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_init_map_token (struct btrfs_map_token*,struct extent_buffer*) ; 
 unsigned int btrfs_item_end_nr (struct extent_buffer*,int) ; 
 struct btrfs_item* btrfs_item_nr (int) ; 
 int btrfs_item_nr_offset (int) ; 
 scalar_t__ btrfs_leaf_free_space (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_mark_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_print_leaf (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_header_nritems (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_set_item_key (struct extent_buffer*,struct btrfs_disk_key*,int) ; 
 int /*<<< orphan*/  btrfs_set_token_item_offset (struct extent_buffer*,struct btrfs_item*,int,struct btrfs_map_token*) ; 
 int /*<<< orphan*/  btrfs_set_token_item_size (struct extent_buffer*,struct btrfs_item*,int,struct btrfs_map_token*) ; 
 int btrfs_token_item_offset (struct extent_buffer*,struct btrfs_item*,struct btrfs_map_token*) ; 
 int /*<<< orphan*/  btrfs_unlock_up_safe (struct btrfs_path*,int) ; 
 int /*<<< orphan*/  fixup_low_keys (struct btrfs_path*,struct btrfs_disk_key*,int) ; 
 unsigned int leaf_data_end (struct extent_buffer*) ; 
 int /*<<< orphan*/  memmove_extent_buffer (struct extent_buffer*,int,int,unsigned int) ; 

void setup_items_for_insert(struct btrfs_root *root, struct btrfs_path *path,
			    const struct btrfs_key *cpu_key, u32 *data_size,
			    u32 total_data, u32 total_size, int nr)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_item *item;
	int i;
	u32 nritems;
	unsigned int data_end;
	struct btrfs_disk_key disk_key;
	struct extent_buffer *leaf;
	int slot;
	struct btrfs_map_token token;

	if (path->slots[0] == 0) {
		btrfs_cpu_key_to_disk(&disk_key, cpu_key);
		fixup_low_keys(path, &disk_key, 1);
	}
	btrfs_unlock_up_safe(path, 1);

	leaf = path->nodes[0];
	slot = path->slots[0];

	nritems = btrfs_header_nritems(leaf);
	data_end = leaf_data_end(leaf);

	if (btrfs_leaf_free_space(leaf) < total_size) {
		btrfs_print_leaf(leaf);
		btrfs_crit(fs_info, "not enough freespace need %u have %d",
			   total_size, btrfs_leaf_free_space(leaf));
		BUG();
	}

	btrfs_init_map_token(&token, leaf);
	if (slot != nritems) {
		unsigned int old_data = btrfs_item_end_nr(leaf, slot);

		if (old_data < data_end) {
			btrfs_print_leaf(leaf);
			btrfs_crit(fs_info, "slot %d old_data %d data_end %d",
				   slot, old_data, data_end);
			BUG();
		}
		/*
		 * item0..itemN ... dataN.offset..dataN.size .. data0.size
		 */
		/* first correct the data pointers */
		for (i = slot; i < nritems; i++) {
			u32 ioff;

			item = btrfs_item_nr(i);
			ioff = btrfs_token_item_offset(leaf, item, &token);
			btrfs_set_token_item_offset(leaf, item,
						    ioff - total_data, &token);
		}
		/* shift the items */
		memmove_extent_buffer(leaf, btrfs_item_nr_offset(slot + nr),
			      btrfs_item_nr_offset(slot),
			      (nritems - slot) * sizeof(struct btrfs_item));

		/* shift the data */
		memmove_extent_buffer(leaf, BTRFS_LEAF_DATA_OFFSET +
			      data_end - total_data, BTRFS_LEAF_DATA_OFFSET +
			      data_end, old_data - data_end);
		data_end = old_data;
	}

	/* setup the item for the new data */
	for (i = 0; i < nr; i++) {
		btrfs_cpu_key_to_disk(&disk_key, cpu_key + i);
		btrfs_set_item_key(leaf, &disk_key, slot + i);
		item = btrfs_item_nr(slot + i);
		btrfs_set_token_item_offset(leaf, item,
					    data_end - data_size[i], &token);
		data_end -= data_size[i];
		btrfs_set_token_item_size(leaf, item, data_size[i], &token);
	}

	btrfs_set_header_nritems(leaf, nritems + nr);
	btrfs_mark_buffer_dirty(leaf);

	if (btrfs_leaf_free_space(leaf) < 0) {
		btrfs_print_leaf(leaf);
		BUG();
	}
}