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
struct tcf_exts {int /*<<< orphan*/  member_0; } ;
struct tcf_chain {int /*<<< orphan*/  index; struct tcf_block* block; } ;
struct tcf_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chain_index; } ;
struct tc_cls_flower_offload {unsigned long cookie; struct tcf_exts* exts; int /*<<< orphan*/ * key; int /*<<< orphan*/ * mask; int /*<<< orphan*/ * dissector; int /*<<< orphan*/  command; TYPE_1__ common; } ;
struct fl_flow_tmplt {int /*<<< orphan*/  dummy_key; int /*<<< orphan*/  mask; int /*<<< orphan*/  dissector; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_CLSFLOWER_TMPLT_CREATE ; 
 int /*<<< orphan*/  TC_SETUP_CLSFLOWER ; 
 int /*<<< orphan*/  tc_setup_cb_call (struct tcf_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct tc_cls_flower_offload*,int) ; 

__attribute__((used)) static void fl_hw_create_tmplt(struct tcf_chain *chain,
			       struct fl_flow_tmplt *tmplt)
{
	struct tc_cls_flower_offload cls_flower = {};
	struct tcf_block *block = chain->block;
	struct tcf_exts dummy_exts = { 0, };

	cls_flower.common.chain_index = chain->index;
	cls_flower.command = TC_CLSFLOWER_TMPLT_CREATE;
	cls_flower.cookie = (unsigned long) tmplt;
	cls_flower.dissector = &tmplt->dissector;
	cls_flower.mask = &tmplt->mask;
	cls_flower.key = &tmplt->dummy_key;
	cls_flower.exts = &dummy_exts;

	/* We don't care if driver (any of them) fails to handle this
	 * call. It serves just as a hint for it.
	 */
	tc_setup_cb_call(block, NULL, TC_SETUP_CLSFLOWER,
			 &cls_flower, false);
}