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
struct tbf_sched_data {int /*<<< orphan*/  qdisc; } ;
struct sk_buff {scalar_t__ len; struct sk_buff* next; } ;
struct TYPE_3__ {int qlen; } ;
struct Qdisc {TYPE_1__ q; } ;
typedef  int netdev_features_t ;
struct TYPE_4__ {scalar_t__ pkt_len; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct sk_buff*) ; 
 int NETIF_F_GSO_MASK ; 
 int NET_XMIT_DROP ; 
 int NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 scalar_t__ net_xmit_drop_count (int) ; 
 int netif_skb_features (struct sk_buff*) ; 
 int qdisc_drop (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 int qdisc_enqueue (struct sk_buff*,int /*<<< orphan*/ ,struct sk_buff**) ; 
 unsigned int qdisc_pkt_len (struct sk_buff*) ; 
 struct tbf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_drop (struct Qdisc*) ; 
 TYPE_2__* qdisc_skb_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_tree_reduce_backlog (struct Qdisc*,int,unsigned int) ; 
 struct sk_buff* skb_gso_segment (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_mark_not_on_list (struct sk_buff*) ; 

__attribute__((used)) static int tbf_segment(struct sk_buff *skb, struct Qdisc *sch,
		       struct sk_buff **to_free)
{
	struct tbf_sched_data *q = qdisc_priv(sch);
	struct sk_buff *segs, *nskb;
	netdev_features_t features = netif_skb_features(skb);
	unsigned int len = 0, prev_len = qdisc_pkt_len(skb);
	int ret, nb;

	segs = skb_gso_segment(skb, features & ~NETIF_F_GSO_MASK);

	if (IS_ERR_OR_NULL(segs))
		return qdisc_drop(skb, sch, to_free);

	nb = 0;
	while (segs) {
		nskb = segs->next;
		skb_mark_not_on_list(segs);
		qdisc_skb_cb(segs)->pkt_len = segs->len;
		len += segs->len;
		ret = qdisc_enqueue(segs, q->qdisc, to_free);
		if (ret != NET_XMIT_SUCCESS) {
			if (net_xmit_drop_count(ret))
				qdisc_qstats_drop(sch);
		} else {
			nb++;
		}
		segs = nskb;
	}
	sch->q.qlen += nb;
	if (nb > 1)
		qdisc_tree_reduce_backlog(sch, 1 - nb, prev_len - len);
	consume_skb(skb);
	return nb > 0 ? NET_XMIT_SUCCESS : NET_XMIT_DROP;
}