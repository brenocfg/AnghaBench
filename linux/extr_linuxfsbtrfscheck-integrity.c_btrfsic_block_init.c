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
struct TYPE_4__ {int /*<<< orphan*/ * bio; } ;
struct TYPE_3__ {scalar_t__ offset; scalar_t__ type; scalar_t__ objectid; } ;
struct btrfsic_block {scalar_t__ flush_gen; scalar_t__ submit_bio_bh_rw; int /*<<< orphan*/  ref_from_list; int /*<<< orphan*/  ref_to_list; int /*<<< orphan*/  all_blocks_node; int /*<<< orphan*/  collision_resolving_node; TYPE_2__ orig_bio_bh_end_io; int /*<<< orphan*/ * orig_bio_bh_private; int /*<<< orphan*/ * next_in_same_bio; scalar_t__ mirror_num; scalar_t__ never_written; scalar_t__ iodone_w_error; scalar_t__ is_iodone; scalar_t__ is_superblock; scalar_t__ is_metadata; TYPE_1__ disk_key; int /*<<< orphan*/  generation; scalar_t__ logical_bytenr; scalar_t__ dev_bytenr; int /*<<< orphan*/ * dev_state; int /*<<< orphan*/  magic_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFSIC_BLOCK_MAGIC_NUMBER ; 
 int /*<<< orphan*/  BTRFSIC_GENERATION_UNKNOWN ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfsic_block_init(struct btrfsic_block *b)
{
	b->magic_num = BTRFSIC_BLOCK_MAGIC_NUMBER;
	b->dev_state = NULL;
	b->dev_bytenr = 0;
	b->logical_bytenr = 0;
	b->generation = BTRFSIC_GENERATION_UNKNOWN;
	b->disk_key.objectid = 0;
	b->disk_key.type = 0;
	b->disk_key.offset = 0;
	b->is_metadata = 0;
	b->is_superblock = 0;
	b->is_iodone = 0;
	b->iodone_w_error = 0;
	b->never_written = 0;
	b->mirror_num = 0;
	b->next_in_same_bio = NULL;
	b->orig_bio_bh_private = NULL;
	b->orig_bio_bh_end_io.bio = NULL;
	INIT_LIST_HEAD(&b->collision_resolving_node);
	INIT_LIST_HEAD(&b->all_blocks_node);
	INIT_LIST_HEAD(&b->ref_to_list);
	INIT_LIST_HEAD(&b->ref_from_list);
	b->submit_bio_bh_rw = 0;
	b->flush_gen = 0;
}