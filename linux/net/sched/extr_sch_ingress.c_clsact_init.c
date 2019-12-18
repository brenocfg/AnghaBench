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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int /*<<< orphan*/  miniq_egress; int /*<<< orphan*/  miniq_ingress; } ;
struct TYPE_2__ {int /*<<< orphan*/ * chain_head_change_priv; void* chain_head_change; int /*<<< orphan*/  binder_type; } ;
struct clsact_sched_data {TYPE_1__ egress_block_info; int /*<<< orphan*/  egress_block; int /*<<< orphan*/  miniqp_egress; TYPE_1__ ingress_block_info; int /*<<< orphan*/  ingress_block; int /*<<< orphan*/  miniqp_ingress; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS ; 
 int /*<<< orphan*/  FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS ; 
 void* clsact_chain_head_change ; 
 int /*<<< orphan*/  mini_qdisc_pair_init (int /*<<< orphan*/ *,struct Qdisc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_inc_egress_queue () ; 
 int /*<<< orphan*/  net_inc_ingress_queue () ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 struct clsact_sched_data* qdisc_priv (struct Qdisc*) ; 
 int tcf_block_get_ext (int /*<<< orphan*/ *,struct Qdisc*,TYPE_1__*,struct netlink_ext_ack*) ; 

__attribute__((used)) static int clsact_init(struct Qdisc *sch, struct nlattr *opt,
		       struct netlink_ext_ack *extack)
{
	struct clsact_sched_data *q = qdisc_priv(sch);
	struct net_device *dev = qdisc_dev(sch);
	int err;

	net_inc_ingress_queue();
	net_inc_egress_queue();

	mini_qdisc_pair_init(&q->miniqp_ingress, sch, &dev->miniq_ingress);

	q->ingress_block_info.binder_type = FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS;
	q->ingress_block_info.chain_head_change = clsact_chain_head_change;
	q->ingress_block_info.chain_head_change_priv = &q->miniqp_ingress;

	err = tcf_block_get_ext(&q->ingress_block, sch, &q->ingress_block_info,
				extack);
	if (err)
		return err;

	mini_qdisc_pair_init(&q->miniqp_egress, sch, &dev->miniq_egress);

	q->egress_block_info.binder_type = FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS;
	q->egress_block_info.chain_head_change = clsact_chain_head_change;
	q->egress_block_info.chain_head_change_priv = &q->miniqp_egress;

	return tcf_block_get_ext(&q->egress_block, sch, &q->egress_block_info, extack);
}