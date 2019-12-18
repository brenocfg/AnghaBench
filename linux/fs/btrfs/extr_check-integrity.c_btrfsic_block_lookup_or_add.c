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
struct btrfsic_state {int print_mask; int /*<<< orphan*/  block_hashtable; int /*<<< orphan*/  all_blocks_list; } ;
struct btrfsic_dev_state {int /*<<< orphan*/  name; } ;
struct btrfsic_block_data_ctx {int /*<<< orphan*/  start; int /*<<< orphan*/  dev_bytenr; TYPE_1__* dev; } ;
struct btrfsic_block {int is_metadata; int is_iodone; int never_written; int mirror_num; int /*<<< orphan*/  all_blocks_node; int /*<<< orphan*/  dev_bytenr; int /*<<< orphan*/  logical_bytenr; struct btrfsic_dev_state* dev_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  bd_dev; } ;
struct TYPE_3__ {TYPE_2__* bdev; } ;

/* Variables and functions */
 int BTRFSIC_PRINT_MASK_VERBOSE ; 
 struct btrfsic_block* btrfsic_block_alloc () ; 
 int /*<<< orphan*/  btrfsic_block_free (struct btrfsic_block*) ; 
 int /*<<< orphan*/  btrfsic_block_hashtable_add (struct btrfsic_block*,int /*<<< orphan*/ *) ; 
 struct btrfsic_block* btrfsic_block_hashtable_lookup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct btrfsic_dev_state* btrfsic_dev_state_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfsic_get_block_type (struct btrfsic_state*,struct btrfsic_block*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static struct btrfsic_block *btrfsic_block_lookup_or_add(
		struct btrfsic_state *state,
		struct btrfsic_block_data_ctx *block_ctx,
		const char *additional_string,
		int is_metadata,
		int is_iodone,
		int never_written,
		int mirror_num,
		int *was_created)
{
	struct btrfsic_block *block;

	block = btrfsic_block_hashtable_lookup(block_ctx->dev->bdev,
					       block_ctx->dev_bytenr,
					       &state->block_hashtable);
	if (NULL == block) {
		struct btrfsic_dev_state *dev_state;

		block = btrfsic_block_alloc();
		if (NULL == block) {
			pr_info("btrfsic: error, kmalloc failed!\n");
			return NULL;
		}
		dev_state = btrfsic_dev_state_lookup(block_ctx->dev->bdev->bd_dev);
		if (NULL == dev_state) {
			pr_info("btrfsic: error, lookup dev_state failed!\n");
			btrfsic_block_free(block);
			return NULL;
		}
		block->dev_state = dev_state;
		block->dev_bytenr = block_ctx->dev_bytenr;
		block->logical_bytenr = block_ctx->start;
		block->is_metadata = is_metadata;
		block->is_iodone = is_iodone;
		block->never_written = never_written;
		block->mirror_num = mirror_num;
		if (state->print_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			pr_info("New %s%c-block @%llu (%s/%llu/%d)\n",
			       additional_string,
			       btrfsic_get_block_type(state, block),
			       block->logical_bytenr, dev_state->name,
			       block->dev_bytenr, mirror_num);
		list_add(&block->all_blocks_node, &state->all_blocks_list);
		btrfsic_block_hashtable_add(block, &state->block_hashtable);
		if (NULL != was_created)
			*was_created = 1;
	} else {
		if (NULL != was_created)
			*was_created = 0;
	}

	return block;
}