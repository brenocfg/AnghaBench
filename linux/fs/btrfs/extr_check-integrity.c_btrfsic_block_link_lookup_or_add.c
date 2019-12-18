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
typedef  void* u64 ;
struct btrfsic_state {int print_mask; int /*<<< orphan*/  block_link_hashtable; } ;
struct btrfsic_block_link {int ref_cnt; void* parent_generation; int /*<<< orphan*/  node_ref_from; int /*<<< orphan*/  node_ref_to; struct btrfsic_block* block_ref_from; struct btrfsic_block* block_ref_to; } ;
struct btrfsic_block_data_ctx {int /*<<< orphan*/  dev_bytenr; TYPE_1__* dev; } ;
struct btrfsic_block {int /*<<< orphan*/  ref_from_list; int /*<<< orphan*/  ref_to_list; int /*<<< orphan*/  dev_bytenr; TYPE_2__* dev_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int BTRFSIC_PRINT_MASK_VERBOSE ; 
 struct btrfsic_block_link* btrfsic_block_link_alloc () ; 
 int /*<<< orphan*/  btrfsic_block_link_hashtable_add (struct btrfsic_block_link*,int /*<<< orphan*/ *) ; 
 struct btrfsic_block_link* btrfsic_block_link_hashtable_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfsic_print_add_link (struct btrfsic_state*,struct btrfsic_block_link*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static struct btrfsic_block_link *btrfsic_block_link_lookup_or_add(
		struct btrfsic_state *state,
		struct btrfsic_block_data_ctx *next_block_ctx,
		struct btrfsic_block *next_block,
		struct btrfsic_block *from_block,
		u64 parent_generation)
{
	struct btrfsic_block_link *l;

	l = btrfsic_block_link_hashtable_lookup(next_block_ctx->dev->bdev,
						next_block_ctx->dev_bytenr,
						from_block->dev_state->bdev,
						from_block->dev_bytenr,
						&state->block_link_hashtable);
	if (NULL == l) {
		l = btrfsic_block_link_alloc();
		if (NULL == l) {
			pr_info("btrfsic: error, kmalloc failed!\n");
			return NULL;
		}

		l->block_ref_to = next_block;
		l->block_ref_from = from_block;
		l->ref_cnt = 1;
		l->parent_generation = parent_generation;

		if (state->print_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			btrfsic_print_add_link(state, l);

		list_add(&l->node_ref_to, &from_block->ref_to_list);
		list_add(&l->node_ref_from, &next_block->ref_from_list);

		btrfsic_block_link_hashtable_add(l,
						 &state->block_link_hashtable);
	} else {
		l->ref_cnt++;
		l->parent_generation = parent_generation;
		if (state->print_mask & BTRFSIC_PRINT_MASK_VERBOSE)
			btrfsic_print_add_link(state, l);
	}

	return l;
}