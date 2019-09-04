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
struct sk_buff {int /*<<< orphan*/  rbnode; int /*<<< orphan*/  tstamp; } ;
struct rb_node {struct rb_node* rb_left; struct rb_node* rb_right; } ;
struct TYPE_4__ {struct rb_node* rb_node; } ;
struct etf_sched_data {TYPE_2__ head; } ;
struct TYPE_3__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  SO_EE_CODE_TXTIME_INVALID_PARAM ; 
 int /*<<< orphan*/  is_packet_valid (struct Qdisc*,struct sk_buff*) ; 
 scalar_t__ ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qdisc_drop (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 struct etf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_inc (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  rb_insert_color (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  rb_link_node (int /*<<< orphan*/ *,struct rb_node*,struct rb_node**) ; 
 struct sk_buff* rb_to_skb (struct rb_node*) ; 
 int /*<<< orphan*/  report_sock_error (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_watchdog (struct Qdisc*) ; 

__attribute__((used)) static int etf_enqueue_timesortedlist(struct sk_buff *nskb, struct Qdisc *sch,
				      struct sk_buff **to_free)
{
	struct etf_sched_data *q = qdisc_priv(sch);
	struct rb_node **p = &q->head.rb_node, *parent = NULL;
	ktime_t txtime = nskb->tstamp;

	if (!is_packet_valid(sch, nskb)) {
		report_sock_error(nskb, EINVAL,
				  SO_EE_CODE_TXTIME_INVALID_PARAM);
		return qdisc_drop(nskb, sch, to_free);
	}

	while (*p) {
		struct sk_buff *skb;

		parent = *p;
		skb = rb_to_skb(parent);
		if (ktime_after(txtime, skb->tstamp))
			p = &parent->rb_right;
		else
			p = &parent->rb_left;
	}
	rb_link_node(&nskb->rbnode, parent, p);
	rb_insert_color(&nskb->rbnode, &q->head);

	qdisc_qstats_backlog_inc(sch, nskb);
	sch->q.qlen++;

	/* Now we may need to re-arm the qdisc watchdog for the next packet. */
	reset_watchdog(sch);

	return NET_XMIT_SUCCESS;
}