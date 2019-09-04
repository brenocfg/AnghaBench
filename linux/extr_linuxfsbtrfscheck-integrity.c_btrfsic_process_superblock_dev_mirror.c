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
typedef  int u64 ;
struct buffer_head {scalar_t__ b_data; } ;
struct btrfsic_state {scalar_t__ metablock_size; scalar_t__ datablock_size; int print_mask; scalar_t__ max_superblock_generation; struct btrfsic_block* latest_superblock; int /*<<< orphan*/  block_hashtable; int /*<<< orphan*/  all_blocks_list; struct btrfs_fs_info* fs_info; } ;
struct btrfsic_dev_state {int /*<<< orphan*/  name; } ;
struct btrfsic_block_link {int dummy; } ;
struct btrfsic_block_data_ctx {int dummy; } ;
struct btrfs_disk_key {scalar_t__ offset; int /*<<< orphan*/  type; } ;
struct btrfsic_block {int dev_bytenr; int logical_bytenr; int is_metadata; int is_superblock; int is_iodone; int mirror_num; scalar_t__ generation; struct btrfs_disk_key disk_key; int /*<<< orphan*/  all_blocks_node; scalar_t__ never_written; struct btrfsic_dev_state* dev_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  uuid; } ;
struct btrfs_super_block {TYPE_1__ dev_item; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_device {scalar_t__ commit_total_bytes; int /*<<< orphan*/  name; int /*<<< orphan*/  uuid; struct block_device* bdev; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ BTRFSIC_GENERATION_UNKNOWN ; 
 int BTRFSIC_PRINT_MASK_INITIAL_ALL_TREES ; 
 int BTRFSIC_PRINT_MASK_NUM_COPIES ; 
 int BTRFSIC_PRINT_MASK_SUPERBLOCK_WRITE ; 
 int BTRFS_BDEV_BLOCKSIZE ; 
 int /*<<< orphan*/  BTRFS_CHUNK_TREE_OBJECTID ; 
 scalar_t__ BTRFS_MAGIC ; 
 int /*<<< orphan*/  BTRFS_ROOT_ITEM_KEY ; 
 int /*<<< orphan*/  BTRFS_ROOT_TREE_OBJECTID ; 
 scalar_t__ BTRFS_SUPER_INFO_SIZE ; 
 int /*<<< orphan*/  BTRFS_TREE_LOG_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_UUID_SIZE ; 
 struct buffer_head* __bread (struct block_device* const,int,scalar_t__) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  btrfs_info_in_rcu (struct btrfs_fs_info*,char*,struct block_device* const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int btrfs_num_copies (struct btrfs_fs_info*,int,scalar_t__) ; 
 int btrfs_sb_offset (int) ; 
 int /*<<< orphan*/  btrfs_set_disk_key_objectid (struct btrfs_disk_key*,int /*<<< orphan*/ ) ; 
 int btrfs_super_bytenr (struct btrfs_super_block*) ; 
 int btrfs_super_chunk_root (struct btrfs_super_block*) ; 
 scalar_t__ btrfs_super_generation (struct btrfs_super_block*) ; 
 int btrfs_super_log_root (struct btrfs_super_block*) ; 
 scalar_t__ btrfs_super_magic (struct btrfs_super_block*) ; 
 scalar_t__ btrfs_super_nodesize (struct btrfs_super_block*) ; 
 int btrfs_super_root (struct btrfs_super_block*) ; 
 scalar_t__ btrfs_super_sectorsize (struct btrfs_super_block*) ; 
 struct btrfsic_block* btrfsic_block_alloc () ; 
 int /*<<< orphan*/  btrfsic_block_hashtable_add (struct btrfsic_block*,int /*<<< orphan*/ *) ; 
 struct btrfsic_block* btrfsic_block_hashtable_lookup (struct block_device* const,int,int /*<<< orphan*/ *) ; 
 struct btrfsic_block_link* btrfsic_block_link_lookup_or_add (struct btrfsic_state*,struct btrfsic_block_data_ctx*,struct btrfsic_block*,struct btrfsic_block*,scalar_t__) ; 
 struct btrfsic_block* btrfsic_block_lookup_or_add (struct btrfsic_state*,struct btrfsic_block_data_ctx*,char const*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfsic_dump_tree_sub (struct btrfsic_state*,struct btrfsic_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfsic_map_block (struct btrfsic_state*,int,scalar_t__,struct btrfsic_block_data_ctx*,int) ; 
 int /*<<< orphan*/  btrfsic_release_block_ctx (struct btrfsic_block_data_ctx*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct btrfs_super_block*,struct btrfs_super_block*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  rcu_str_deref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btrfsic_process_superblock_dev_mirror(
		struct btrfsic_state *state,
		struct btrfsic_dev_state *dev_state,
		struct btrfs_device *device,
		int superblock_mirror_num,
		struct btrfsic_dev_state **selected_dev_state,
		struct btrfs_super_block *selected_super)
{
	struct btrfs_fs_info *fs_info = state->fs_info;
	struct btrfs_super_block *super_tmp;
	u64 dev_bytenr;
	struct buffer_head *bh;
	struct btrfsic_block *superblock_tmp;
	int pass;
	struct block_device *const superblock_bdev = device->bdev;

	/* super block bytenr is always the unmapped device bytenr */
	dev_bytenr = btrfs_sb_offset(superblock_mirror_num);
	if (dev_bytenr + BTRFS_SUPER_INFO_SIZE > device->commit_total_bytes)
		return -1;
	bh = __bread(superblock_bdev, dev_bytenr / BTRFS_BDEV_BLOCKSIZE,
		     BTRFS_SUPER_INFO_SIZE);
	if (NULL == bh)
		return -1;
	super_tmp = (struct btrfs_super_block *)
	    (bh->b_data + (dev_bytenr & (BTRFS_BDEV_BLOCKSIZE - 1)));

	if (btrfs_super_bytenr(super_tmp) != dev_bytenr ||
	    btrfs_super_magic(super_tmp) != BTRFS_MAGIC ||
	    memcmp(device->uuid, super_tmp->dev_item.uuid, BTRFS_UUID_SIZE) ||
	    btrfs_super_nodesize(super_tmp) != state->metablock_size ||
	    btrfs_super_sectorsize(super_tmp) != state->datablock_size) {
		brelse(bh);
		return 0;
	}

	superblock_tmp =
	    btrfsic_block_hashtable_lookup(superblock_bdev,
					   dev_bytenr,
					   &state->block_hashtable);
	if (NULL == superblock_tmp) {
		superblock_tmp = btrfsic_block_alloc();
		if (NULL == superblock_tmp) {
			pr_info("btrfsic: error, kmalloc failed!\n");
			brelse(bh);
			return -1;
		}
		/* for superblock, only the dev_bytenr makes sense */
		superblock_tmp->dev_bytenr = dev_bytenr;
		superblock_tmp->dev_state = dev_state;
		superblock_tmp->logical_bytenr = dev_bytenr;
		superblock_tmp->generation = btrfs_super_generation(super_tmp);
		superblock_tmp->is_metadata = 1;
		superblock_tmp->is_superblock = 1;
		superblock_tmp->is_iodone = 1;
		superblock_tmp->never_written = 0;
		superblock_tmp->mirror_num = 1 + superblock_mirror_num;
		if (state->print_mask & BTRFSIC_PRINT_MASK_SUPERBLOCK_WRITE)
			btrfs_info_in_rcu(fs_info,
				"new initial S-block (bdev %p, %s) @%llu (%s/%llu/%d)",
				     superblock_bdev,
				     rcu_str_deref(device->name), dev_bytenr,
				     dev_state->name, dev_bytenr,
				     superblock_mirror_num);
		list_add(&superblock_tmp->all_blocks_node,
			 &state->all_blocks_list);
		btrfsic_block_hashtable_add(superblock_tmp,
					    &state->block_hashtable);
	}

	/* select the one with the highest generation field */
	if (btrfs_super_generation(super_tmp) >
	    state->max_superblock_generation ||
	    0 == state->max_superblock_generation) {
		memcpy(selected_super, super_tmp, sizeof(*selected_super));
		*selected_dev_state = dev_state;
		state->max_superblock_generation =
		    btrfs_super_generation(super_tmp);
		state->latest_superblock = superblock_tmp;
	}

	for (pass = 0; pass < 3; pass++) {
		u64 next_bytenr;
		int num_copies;
		int mirror_num;
		const char *additional_string = NULL;
		struct btrfs_disk_key tmp_disk_key;

		tmp_disk_key.type = BTRFS_ROOT_ITEM_KEY;
		tmp_disk_key.offset = 0;
		switch (pass) {
		case 0:
			btrfs_set_disk_key_objectid(&tmp_disk_key,
						    BTRFS_ROOT_TREE_OBJECTID);
			additional_string = "initial root ";
			next_bytenr = btrfs_super_root(super_tmp);
			break;
		case 1:
			btrfs_set_disk_key_objectid(&tmp_disk_key,
						    BTRFS_CHUNK_TREE_OBJECTID);
			additional_string = "initial chunk ";
			next_bytenr = btrfs_super_chunk_root(super_tmp);
			break;
		case 2:
			btrfs_set_disk_key_objectid(&tmp_disk_key,
						    BTRFS_TREE_LOG_OBJECTID);
			additional_string = "initial log ";
			next_bytenr = btrfs_super_log_root(super_tmp);
			if (0 == next_bytenr)
				continue;
			break;
		}

		num_copies = btrfs_num_copies(fs_info, next_bytenr,
					      state->metablock_size);
		if (state->print_mask & BTRFSIC_PRINT_MASK_NUM_COPIES)
			pr_info("num_copies(log_bytenr=%llu) = %d\n",
			       next_bytenr, num_copies);
		for (mirror_num = 1; mirror_num <= num_copies; mirror_num++) {
			struct btrfsic_block *next_block;
			struct btrfsic_block_data_ctx tmp_next_block_ctx;
			struct btrfsic_block_link *l;

			if (btrfsic_map_block(state, next_bytenr,
					      state->metablock_size,
					      &tmp_next_block_ctx,
					      mirror_num)) {
				pr_info("btrfsic: btrfsic_map_block(bytenr @%llu, mirror %d) failed!\n",
				       next_bytenr, mirror_num);
				brelse(bh);
				return -1;
			}

			next_block = btrfsic_block_lookup_or_add(
					state, &tmp_next_block_ctx,
					additional_string, 1, 1, 0,
					mirror_num, NULL);
			if (NULL == next_block) {
				btrfsic_release_block_ctx(&tmp_next_block_ctx);
				brelse(bh);
				return -1;
			}

			next_block->disk_key = tmp_disk_key;
			next_block->generation = BTRFSIC_GENERATION_UNKNOWN;
			l = btrfsic_block_link_lookup_or_add(
					state, &tmp_next_block_ctx,
					next_block, superblock_tmp,
					BTRFSIC_GENERATION_UNKNOWN);
			btrfsic_release_block_ctx(&tmp_next_block_ctx);
			if (NULL == l) {
				brelse(bh);
				return -1;
			}
		}
	}
	if (state->print_mask & BTRFSIC_PRINT_MASK_INITIAL_ALL_TREES)
		btrfsic_dump_tree_sub(state, superblock_tmp, 0);

	brelse(bh);
	return 0;
}