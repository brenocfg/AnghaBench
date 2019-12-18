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
struct tbf_sched_data {unsigned int max_size; int /*<<< orphan*/  qdisc; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_3__ {unsigned int backlog; } ;
struct Qdisc {TYPE_2__ q; TYPE_1__ qstats; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
 scalar_t__ net_xmit_drop_count (int) ; 
 int qdisc_drop (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 int qdisc_enqueue (struct sk_buff*,int /*<<< orphan*/ ,struct sk_buff**) ; 
 unsigned int qdisc_pkt_len (struct sk_buff*) ; 
 struct tbf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_drop (struct Qdisc*) ; 
 scalar_t__ skb_gso_validate_mac_len (struct sk_buff*,unsigned int) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int tbf_segment (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 

__attribute__((used)) static int tbf_enqueue(struct sk_buff *skb, struct Qdisc *sch,
		       struct sk_buff **to_free)
{
	struct tbf_sched_data *q = qdisc_priv(sch);
	unsigned int len = qdisc_pkt_len(skb);
	int ret;

	if (qdisc_pkt_len(skb) > q->max_size) {
		if (skb_is_gso(skb) &&
		    skb_gso_validate_mac_len(skb, q->max_size))
			return tbf_segment(skb, sch, to_free);
		return qdisc_drop(skb, sch, to_free);
	}
	ret = qdisc_enqueue(skb, q->qdisc, to_free);
	if (ret != NET_XMIT_SUCCESS) {
		if (net_xmit_drop_count(ret))
			qdisc_qstats_drop(sch);
		return ret;
	}

	sch->qstats.backlog += len;
	sch->q.qlen++;
	return NET_XMIT_SUCCESS;
}