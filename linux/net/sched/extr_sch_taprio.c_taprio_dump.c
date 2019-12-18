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
struct tc_mqprio_qopt {unsigned int num_tc; int /*<<< orphan*/ * offset; int /*<<< orphan*/ * count; int /*<<< orphan*/  prio_tc_map; int /*<<< orphan*/  member_0; } ;
struct taprio_sched {scalar_t__ txtime_delay; scalar_t__ flags; int /*<<< orphan*/  clockid; int /*<<< orphan*/  admin_sched; int /*<<< orphan*/  oper_sched; } ;
struct sk_buff {int dummy; } ;
struct sched_gate_list {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {TYPE_1__* tc_to_txq; int /*<<< orphan*/  prio_tc_map; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  opt ;
struct TYPE_2__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  FULL_OFFLOAD_IS_ENABLED (scalar_t__) ; 
 int /*<<< orphan*/  TCA_OPTIONS ; 
 int /*<<< orphan*/  TCA_TAPRIO_ATTR_ADMIN_SCHED ; 
 int /*<<< orphan*/  TCA_TAPRIO_ATTR_FLAGS ; 
 int /*<<< orphan*/  TCA_TAPRIO_ATTR_PRIOMAP ; 
 int /*<<< orphan*/  TCA_TAPRIO_ATTR_SCHED_CLOCKID ; 
 int /*<<< orphan*/  TCA_TAPRIO_ATTR_TXTIME_DELAY ; 
 scalar_t__ dump_schedule (struct sk_buff*,struct sched_gate_list*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int netdev_get_num_tc (struct net_device*) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct tc_mqprio_qopt*) ; 
 scalar_t__ nla_put_s32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 struct taprio_sched* qdisc_priv (struct Qdisc*) ; 
 struct sched_gate_list* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int taprio_dump(struct Qdisc *sch, struct sk_buff *skb)
{
	struct taprio_sched *q = qdisc_priv(sch);
	struct net_device *dev = qdisc_dev(sch);
	struct sched_gate_list *oper, *admin;
	struct tc_mqprio_qopt opt = { 0 };
	struct nlattr *nest, *sched_nest;
	unsigned int i;

	rcu_read_lock();
	oper = rcu_dereference(q->oper_sched);
	admin = rcu_dereference(q->admin_sched);

	opt.num_tc = netdev_get_num_tc(dev);
	memcpy(opt.prio_tc_map, dev->prio_tc_map, sizeof(opt.prio_tc_map));

	for (i = 0; i < netdev_get_num_tc(dev); i++) {
		opt.count[i] = dev->tc_to_txq[i].count;
		opt.offset[i] = dev->tc_to_txq[i].offset;
	}

	nest = nla_nest_start_noflag(skb, TCA_OPTIONS);
	if (!nest)
		goto start_error;

	if (nla_put(skb, TCA_TAPRIO_ATTR_PRIOMAP, sizeof(opt), &opt))
		goto options_error;

	if (!FULL_OFFLOAD_IS_ENABLED(q->flags) &&
	    nla_put_s32(skb, TCA_TAPRIO_ATTR_SCHED_CLOCKID, q->clockid))
		goto options_error;

	if (q->flags && nla_put_u32(skb, TCA_TAPRIO_ATTR_FLAGS, q->flags))
		goto options_error;

	if (q->txtime_delay &&
	    nla_put_u32(skb, TCA_TAPRIO_ATTR_TXTIME_DELAY, q->txtime_delay))
		goto options_error;

	if (oper && dump_schedule(skb, oper))
		goto options_error;

	if (!admin)
		goto done;

	sched_nest = nla_nest_start_noflag(skb, TCA_TAPRIO_ATTR_ADMIN_SCHED);
	if (!sched_nest)
		goto options_error;

	if (dump_schedule(skb, admin))
		goto admin_error;

	nla_nest_end(skb, sched_nest);

done:
	rcu_read_unlock();

	return nla_nest_end(skb, nest);

admin_error:
	nla_nest_cancel(skb, sched_nest);

options_error:
	nla_nest_cancel(skb, nest);

start_error:
	rcu_read_unlock();
	return -ENOSPC;
}