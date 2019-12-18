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
struct btrfsic_state {int print_mask; int /*<<< orphan*/  block_link_hashtable; int /*<<< orphan*/  metablock_size; struct btrfs_fs_info* fs_info; } ;
struct btrfsic_block_link {int ref_cnt; int parent_generation; int /*<<< orphan*/  node_ref_from; int /*<<< orphan*/  node_ref_to; struct btrfsic_block* block_ref_from; struct btrfsic_block* block_ref_to; } ;
struct btrfsic_block_data_ctx {scalar_t__ len; int /*<<< orphan*/  dev_bytenr; TYPE_1__* dev; } ;
struct btrfs_disk_key {int dummy; } ;
struct btrfsic_block {int logical_bytenr; int mirror_num; int /*<<< orphan*/  ref_from_list; int /*<<< orphan*/  ref_to_list; struct btrfs_disk_key disk_key; int /*<<< orphan*/  is_metadata; int /*<<< orphan*/  generation; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFSIC_GENERATION_UNKNOWN ; 
 int BTRFSIC_PRINT_MASK_NUM_COPIES ; 
 int BTRFSIC_PRINT_MASK_VERBOSE ; 
 int btrfs_num_copies (struct btrfs_fs_info*,int,int /*<<< orphan*/ ) ; 
 struct btrfsic_block_link* btrfsic_block_link_alloc () ; 
 int /*<<< orphan*/  btrfsic_block_link_hashtable_add (struct btrfsic_block_link*,int /*<<< orphan*/ *) ; 
 struct btrfsic_block_link* btrfsic_block_link_hashtable_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct btrfsic_block* btrfsic_block_lookup_or_add (struct btrfsic_state*,struct btrfsic_block_data_ctx*,char*,int,int,int,int,int*) ; 
 int /*<<< orphan*/  btrfsic_get_block_type (struct btrfsic_state*,struct btrfsic_block*) ; 
 int btrfsic_map_block (struct btrfsic_state*,int,int /*<<< orphan*/ ,struct btrfsic_block_data_ctx*,int) ; 
 int /*<<< orphan*/  btrfsic_print_add_link (struct btrfsic_state*,struct btrfsic_block_link*) ; 
 int btrfsic_read_block (struct btrfsic_state*,struct btrfsic_block_data_ctx*) ; 
 int /*<<< orphan*/  btrfsic_release_block_ctx (struct btrfsic_block_data_ctx*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static int btrfsic_create_link_to_next_block(
		struct btrfsic_state *state,
		struct btrfsic_block *block,
		struct btrfsic_block_data_ctx *block_ctx,
		u64 next_bytenr,
		int limit_nesting,
		struct btrfsic_block_data_ctx *next_block_ctx,
		struct btrfsic_block **next_blockp,
		int force_iodone_flag,
		int *num_copiesp, int *mirror_nump,
		struct btrfs_disk_key *disk_key,
		u64 parent_generation)
{
	struct btrfs_fs_info *fs_info = state->fs_info;
	struct btrfsic_block *next_block = NULL;
	int ret;
	struct btrfsic_block_link *l;
	int did_alloc_block_link;
	int block_was_created;

	*next_blockp = NULL;
	if (0 == *num_copiesp) {
		*num_copiesp = btrfs_num_copies(fs_info, next_bytenr,
						state->metablock_size);
		if (state->print_mask & BTRFSIC_PRINT_MASK_NUM_COPIES)
			pr_info("num_copies(log_bytenr=%llu) = %d\n",
			       next_bytenr, *num_copiesp);
		*mirror_nump = 1;
	}

	if (*mirror_nump > *num_copiesp)
		return 0;

	if (state->print_mask & BTRFSIC_PRINT_MASK_VERBOSE)
		pr_info("btrfsic_create_link_to_next_block(mirror_num=%d)\n",
		       *mirror_nump);
	ret = btrfsic_map_block(state, next_bytenr,
				state->metablock_size,
				next_block_ctx, *mirror_nump);
	if (ret) {
		pr_info("btrfsic: btrfsic_map_block(@%llu, mirror=%d) failed!\n",
		       next_bytenr, *mirror_nump);
		btrfsic_release_block_ctx(next_block_ctx);
		*next_blockp = NULL;
		return -1;
	}

	next_block = btrfsic_block_lookup_or_add(state,
						 next_block_ctx, "referenced ",
						 1, force_iodone_flag,
						 !force_iodone_flag,
						 *mirror_nump,
						 &block_was_created);
	if (NULL == next_block) {
		btrfsic_release_block_ctx(next_block_ctx);
		*next_blockp = NULL;
		return -1;
	}
	if (block_was_created) {
		l = NULL;
		next_block->generation = BTRFSIC_GENERATION_UNKNOWN;
	} else {
		if (state->print_mask & BTRFSIC_PRINT_MASK_VERBOSE) {
			if (next_block->logical_bytenr != next_bytenr &&
			    !(!next_block->is_metadata &&
			      0 == next_block->logical_bytenr))
				pr_info("Referenced block @%llu (%s/%llu/%d) found in hash table, %c, bytenr mismatch (!= stored %llu).\n",
				       next_bytenr, next_block_ctx->dev->name,
				       next_block_ctx->dev_bytenr, *mirror_nump,
				       btrfsic_get_block_type(state,
							      next_block),
				       next_block->logical_bytenr);
			else
				pr_info("Referenced block @%llu (%s/%llu/%d) found in hash table, %c.\n",
				       next_bytenr, next_block_ctx->dev->name,
				       next_block_ctx->dev_bytenr, *mirror_nump,
				       btrfsic_get_block_type(state,
							      next_block));
		}
		next_block->logical_bytenr = next_bytenr;

		next_block->mirror_num = *mirror_nump;
		l = btrfsic_block_link_hashtable_lookup(
				next_block_ctx->dev->bdev,
				next_block_ctx->dev_bytenr,
				block_ctx->dev->bdev,
				block_ctx->dev_bytenr,
				&state->block_link_hashtable);
	}

	next_block->disk_key = *disk_key;
	if (NULL == l) {
		l = btrfsic_block_link_alloc();
		if (NULL == l) {
			pr_info("btrfsic: error, kmalloc failed!\n");
			btrfsic_release_block_ctx(next_block_ctx);
			*next_blockp = NULL;
			return -1;
		}

		did_alloc_block_link = 1;
		l->block_ref_to = next_block;
		l->block_ref_from = block;
		l->ref_cnt = 1;
		l->parent_generation = parent_generation;

		if (state->print_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			btrfsic_print_add_link(state, l);

		list_add(&l->node_ref_to, &block->ref_to_list);
		list_add(&l->node_ref_from, &next_block->ref_from_list);

		btrfsic_block_link_hashtable_add(l,
						 &state->block_link_hashtable);
	} else {
		did_alloc_block_link = 0;
		if (0 == limit_nesting) {
			l->ref_cnt++;
			l->parent_generation = parent_generation;
			if (state->print_mask & BTRFSIC_PRINT_MASK_VERBOSE)
				btrfsic_print_add_link(state, l);
		}
	}

	if (limit_nesting > 0 && did_alloc_block_link) {
		ret = btrfsic_read_block(state, next_block_ctx);
		if (ret < (int)next_block_ctx->len) {
			pr_info("btrfsic: read block @logical %llu failed!\n",
			       next_bytenr);
			btrfsic_release_block_ctx(next_block_ctx);
			*next_blockp = NULL;
			return -1;
		}

		*next_blockp = next_block;
	} else {
		*next_blockp = NULL;
	}
	(*mirror_nump)++;

	return 0;
}