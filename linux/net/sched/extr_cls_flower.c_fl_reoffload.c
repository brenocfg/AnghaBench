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
struct cls_fl_filter {int /*<<< orphan*/  in_hw_count; int /*<<< orphan*/  flags; TYPE_4__ res; int /*<<< orphan*/  exts; int /*<<< orphan*/  mkey; TYPE_2__* mask; } ;
typedef  int /*<<< orphan*/  flow_setup_cb_t ;
struct TYPE_9__ {int /*<<< orphan*/ * key; int /*<<< orphan*/ * mask; int /*<<< orphan*/ * dissector; } ;
struct TYPE_11__ {int /*<<< orphan*/  action; TYPE_3__ match; } ;
struct TYPE_8__ {int /*<<< orphan*/  key; int /*<<< orphan*/  dissector; } ;
struct TYPE_7__ {struct tcf_block* block; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FLOW_CLS_DESTROY ; 
 int /*<<< orphan*/  FLOW_CLS_REPLACE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  TC_SETUP_CLSFLOWER ; 
 int /*<<< orphan*/  __fl_put (struct cls_fl_filter*) ; 
 struct cls_fl_filter* fl_get_next_hw_filter (struct tcf_proto*,struct cls_fl_filter*,int) ; 
 TYPE_5__* flow_rule_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 int /*<<< orphan*/  tc_cleanup_flow_action (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_cls_common_offload_init (int /*<<< orphan*/ *,struct tcf_proto*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int tc_setup_cb_reoffload (struct tcf_block*,struct tcf_proto*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct flow_cls_offload*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int tc_setup_flow_action (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ tc_skip_sw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_exts_num_actions (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fl_reoffload(struct tcf_proto *tp, bool add, flow_setup_cb_t *cb,
			void *cb_priv, struct netlink_ext_ack *extack)
{
	struct tcf_block *block = tp->chain->block;
	struct flow_cls_offload cls_flower = {};
	struct cls_fl_filter *f = NULL;
	int err;

	/* hw_filters list can only be changed by hw offload functions after
	 * obtaining rtnl lock. Make sure it is not changed while reoffload is
	 * iterating it.
	 */
	ASSERT_RTNL();

	while ((f = fl_get_next_hw_filter(tp, f, add))) {
		cls_flower.rule =
			flow_rule_alloc(tcf_exts_num_actions(&f->exts));
		if (!cls_flower.rule) {
			__fl_put(f);
			return -ENOMEM;
		}

		tc_cls_common_offload_init(&cls_flower.common, tp, f->flags,
					   extack);
		cls_flower.command = add ?
			FLOW_CLS_REPLACE : FLOW_CLS_DESTROY;
		cls_flower.cookie = (unsigned long)f;
		cls_flower.rule->match.dissector = &f->mask->dissector;
		cls_flower.rule->match.mask = &f->mask->key;
		cls_flower.rule->match.key = &f->mkey;

		err = tc_setup_flow_action(&cls_flower.rule->action, &f->exts,
					   true);
		if (err) {
			kfree(cls_flower.rule);
			if (tc_skip_sw(f->flags)) {
				NL_SET_ERR_MSG_MOD(extack, "Failed to setup flow action");
				__fl_put(f);
				return err;
			}
			goto next_flow;
		}

		cls_flower.classid = f->res.classid;

		err = tc_setup_cb_reoffload(block, tp, add, cb,
					    TC_SETUP_CLSFLOWER, &cls_flower,
					    cb_priv, &f->flags,
					    &f->in_hw_count);
		tc_cleanup_flow_action(&cls_flower.rule->action);
		kfree(cls_flower.rule);

		if (err) {
			__fl_put(f);
			return err;
		}
next_flow:
		__fl_put(f);
	}

	return 0;
}