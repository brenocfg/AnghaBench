#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct tcf_proto {TYPE_1__* chain; } ;
struct tcf_block {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct flow_cls_offload {unsigned long cookie; TYPE_5__* rule; int /*<<< orphan*/  classid; int /*<<< orphan*/  command; int /*<<< orphan*/  common; } ;
struct TYPE_10__ {int /*<<< orphan*/  classid; } ;
struct cls_fl_filter {int flags; int /*<<< orphan*/  in_hw_count; int /*<<< orphan*/  exts; TYPE_4__ res; int /*<<< orphan*/  mkey; TYPE_2__* mask; } ;
struct TYPE_9__ {int /*<<< orphan*/ * key; int /*<<< orphan*/ * mask; int /*<<< orphan*/ * dissector; } ;
struct TYPE_11__ {int /*<<< orphan*/  action; TYPE_3__ match; } ;
struct TYPE_8__ {int /*<<< orphan*/  key; int /*<<< orphan*/  dissector; } ;
struct TYPE_7__ {struct tcf_block* block; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FLOW_CLS_REPLACE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int TCA_CLS_FLAGS_IN_HW ; 
 int /*<<< orphan*/  TC_SETUP_CLSFLOWER ; 
 int /*<<< orphan*/  fl_hw_destroy_filter (struct tcf_proto*,struct cls_fl_filter*,int,int /*<<< orphan*/ *) ; 
 TYPE_5__* flow_rule_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 int /*<<< orphan*/  tc_cleanup_flow_action (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int,struct netlink_ext_ack*) ; 
 int tc_setup_cb_add (struct tcf_block*,struct tcf_proto*,int /*<<< orphan*/ ,struct flow_cls_offload*,int,int*,int /*<<< orphan*/ *,int) ; 
 int tc_setup_flow_action (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int tc_skip_sw (int) ; 
 int /*<<< orphan*/  tcf_exts_num_actions (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fl_hw_replace_filter(struct tcf_proto *tp,
				struct cls_fl_filter *f, bool rtnl_held,
				struct netlink_ext_ack *extack)
{
	struct tcf_block *block = tp->chain->block;
	struct flow_cls_offload cls_flower = {};
	bool skip_sw = tc_skip_sw(f->flags);
	int err = 0;

	cls_flower.rule = flow_rule_alloc(tcf_exts_num_actions(&f->exts));
	if (!cls_flower.rule)
		return -ENOMEM;

	tc_cls_common_offload_init(&cls_flower.common, tp, f->flags, extack);
	cls_flower.command = FLOW_CLS_REPLACE;
	cls_flower.cookie = (unsigned long) f;
	cls_flower.rule->match.dissector = &f->mask->dissector;
	cls_flower.rule->match.mask = &f->mask->key;
	cls_flower.rule->match.key = &f->mkey;
	cls_flower.classid = f->res.classid;

	err = tc_setup_flow_action(&cls_flower.rule->action, &f->exts,
				   rtnl_held);
	if (err) {
		kfree(cls_flower.rule);
		if (skip_sw) {
			NL_SET_ERR_MSG_MOD(extack, "Failed to setup flow action");
			return err;
		}
		return 0;
	}

	err = tc_setup_cb_add(block, tp, TC_SETUP_CLSFLOWER, &cls_flower,
			      skip_sw, &f->flags, &f->in_hw_count, rtnl_held);
	tc_cleanup_flow_action(&cls_flower.rule->action);
	kfree(cls_flower.rule);

	if (err) {
		fl_hw_destroy_filter(tp, f, rtnl_held, NULL);
		return err;
	}

	if (skip_sw && !(f->flags & TCA_CLS_FLAGS_IN_HW))
		return -EINVAL;

	return 0;
}