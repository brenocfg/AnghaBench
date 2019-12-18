#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tcf_chain {int /*<<< orphan*/  index; struct tcf_block* block; } ;
struct tcf_block {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  chain_index; } ;
struct flow_cls_offload {unsigned long cookie; TYPE_3__* rule; int /*<<< orphan*/  command; TYPE_1__ common; } ;
struct fl_flow_tmplt {int /*<<< orphan*/  dummy_key; int /*<<< orphan*/  mask; int /*<<< orphan*/  dissector; } ;
struct TYPE_6__ {int /*<<< orphan*/ * key; int /*<<< orphan*/ * mask; int /*<<< orphan*/ * dissector; } ;
struct TYPE_7__ {TYPE_2__ match; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FLOW_CLS_TMPLT_CREATE ; 
 int /*<<< orphan*/  TC_SETUP_CLSFLOWER ; 
 TYPE_3__* flow_rule_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  tc_setup_cb_call (struct tcf_block*,int /*<<< orphan*/ ,struct flow_cls_offload*,int,int) ; 

__attribute__((used)) static int fl_hw_create_tmplt(struct tcf_chain *chain,
			      struct fl_flow_tmplt *tmplt)
{
	struct flow_cls_offload cls_flower = {};
	struct tcf_block *block = chain->block;

	cls_flower.rule = flow_rule_alloc(0);
	if (!cls_flower.rule)
		return -ENOMEM;

	cls_flower.common.chain_index = chain->index;
	cls_flower.command = FLOW_CLS_TMPLT_CREATE;
	cls_flower.cookie = (unsigned long) tmplt;
	cls_flower.rule->match.dissector = &tmplt->dissector;
	cls_flower.rule->match.mask = &tmplt->mask;
	cls_flower.rule->match.key = &tmplt->dummy_key;

	/* We don't care if driver (any of them) fails to handle this
	 * call. It serves just as a hint for it.
	 */
	tc_setup_cb_call(block, TC_SETUP_CLSFLOWER, &cls_flower, false, true);
	kfree(cls_flower.rule);

	return 0;
}