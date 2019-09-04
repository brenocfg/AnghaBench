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
typedef  size_t u32 ;
struct sk_buff {struct sk_buff* next; } ;
struct nlattr {int dummy; } ;
struct gnet_stats_queue {int /*<<< orphan*/  qlen; int /*<<< orphan*/  drops; int /*<<< orphan*/  backlog; int /*<<< orphan*/  member_0; } ;
struct gnet_dump {int /*<<< orphan*/  skb; } ;
struct cake_tin_data {int /*<<< orphan*/ * backlogs; struct cake_flow* flows; } ;
struct cake_sched_data {size_t tin_cnt; size_t* tin_order; struct cake_tin_data* tins; } ;
struct TYPE_2__ {int /*<<< orphan*/  drop_next; scalar_t__ dropping; int /*<<< orphan*/  blue_timer; scalar_t__ p_drop; scalar_t__ count; } ;
struct cake_flow {TYPE_1__ cvars; int /*<<< orphan*/  deficit; int /*<<< orphan*/  dropped; struct sk_buff* head; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 size_t CAKE_QUEUES ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_BLUE_TIMER_US ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_COBALT_COUNT ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_DEFICIT ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_DROPPING ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_DROP_NEXT_US ; 
 int /*<<< orphan*/  TCA_CAKE_STATS_P_DROP ; 
 int /*<<< orphan*/  TCA_STATS_APP ; 
 scalar_t__ gnet_stats_copy_queue (struct gnet_dump*,int /*<<< orphan*/ *,struct gnet_stats_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_cancel (int /*<<< orphan*/ ,struct nlattr*) ; 
 scalar_t__ nla_nest_end (int /*<<< orphan*/ ,struct nlattr*) ; 
 struct nlattr* nla_nest_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_s32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct cake_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_lock (struct Qdisc*) ; 
 int /*<<< orphan*/  sch_tree_unlock (struct Qdisc*) ; 

__attribute__((used)) static int cake_dump_class_stats(struct Qdisc *sch, unsigned long cl,
				 struct gnet_dump *d)
{
	struct cake_sched_data *q = qdisc_priv(sch);
	const struct cake_flow *flow = NULL;
	struct gnet_stats_queue qs = { 0 };
	struct nlattr *stats;
	u32 idx = cl - 1;

	if (idx < CAKE_QUEUES * q->tin_cnt) {
		const struct cake_tin_data *b = \
			&q->tins[q->tin_order[idx / CAKE_QUEUES]];
		const struct sk_buff *skb;

		flow = &b->flows[idx % CAKE_QUEUES];

		if (flow->head) {
			sch_tree_lock(sch);
			skb = flow->head;
			while (skb) {
				qs.qlen++;
				skb = skb->next;
			}
			sch_tree_unlock(sch);
		}
		qs.backlog = b->backlogs[idx % CAKE_QUEUES];
		qs.drops = flow->dropped;
	}
	if (gnet_stats_copy_queue(d, NULL, &qs, qs.qlen) < 0)
		return -1;
	if (flow) {
		ktime_t now = ktime_get();

		stats = nla_nest_start(d->skb, TCA_STATS_APP);
		if (!stats)
			return -1;

#define PUT_STAT_U32(attr, data) do {				       \
		if (nla_put_u32(d->skb, TCA_CAKE_STATS_ ## attr, data)) \
			goto nla_put_failure;			       \
	} while (0)
#define PUT_STAT_S32(attr, data) do {				       \
		if (nla_put_s32(d->skb, TCA_CAKE_STATS_ ## attr, data)) \
			goto nla_put_failure;			       \
	} while (0)

		PUT_STAT_S32(DEFICIT, flow->deficit);
		PUT_STAT_U32(DROPPING, flow->cvars.dropping);
		PUT_STAT_U32(COBALT_COUNT, flow->cvars.count);
		PUT_STAT_U32(P_DROP, flow->cvars.p_drop);
		if (flow->cvars.p_drop) {
			PUT_STAT_S32(BLUE_TIMER_US,
				     ktime_to_us(
					     ktime_sub(now,
						     flow->cvars.blue_timer)));
		}
		if (flow->cvars.dropping) {
			PUT_STAT_S32(DROP_NEXT_US,
				     ktime_to_us(
					     ktime_sub(now,
						       flow->cvars.drop_next)));
		}

		if (nla_nest_end(d->skb, stats) < 0)
			return -1;
	}

	return 0;

nla_put_failure:
	nla_nest_cancel(d->skb, stats);
	return -1;
}