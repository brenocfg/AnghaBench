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
struct btrfsic_state {int dummy; } ;
struct btrfsic_block_link {TYPE_2__* block_ref_to; TYPE_2__* block_ref_from; int /*<<< orphan*/  ref_cnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  mirror_num; int /*<<< orphan*/  dev_bytenr; TYPE_1__* dev_state; int /*<<< orphan*/  logical_bytenr; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfsic_get_block_type (struct btrfsic_state const*,TYPE_2__*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btrfsic_print_rem_link(const struct btrfsic_state *state,
				   const struct btrfsic_block_link *l)
{
	pr_info("Rem %u* link from %c @%llu (%s/%llu/%d) to %c @%llu (%s/%llu/%d).\n",
	       l->ref_cnt,
	       btrfsic_get_block_type(state, l->block_ref_from),
	       l->block_ref_from->logical_bytenr,
	       l->block_ref_from->dev_state->name,
	       l->block_ref_from->dev_bytenr, l->block_ref_from->mirror_num,
	       btrfsic_get_block_type(state, l->block_ref_to),
	       l->block_ref_to->logical_bytenr,
	       l->block_ref_to->dev_state->name, l->block_ref_to->dev_bytenr,
	       l->block_ref_to->mirror_num);
}