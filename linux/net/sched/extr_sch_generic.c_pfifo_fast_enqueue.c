#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct skb_array {int dummy; } ;
struct sk_buff {size_t priority; } ;
struct pfifo_fast_priv {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
 size_t TC_PRIO_MAX ; 
 struct skb_array* band2list (struct pfifo_fast_priv*,int) ; 
 int* prio2band ; 
 int qdisc_drop (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 int qdisc_drop_cpu (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 scalar_t__ qdisc_is_percpu_stats (struct Qdisc*) ; 
 unsigned int qdisc_pkt_len (struct sk_buff*) ; 
 struct pfifo_fast_priv* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_update_stats_at_enqueue (struct Qdisc*,unsigned int) ; 
 int skb_array_produce (struct skb_array*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pfifo_fast_enqueue(struct sk_buff *skb, struct Qdisc *qdisc,
			      struct sk_buff **to_free)
{
	int band = prio2band[skb->priority & TC_PRIO_MAX];
	struct pfifo_fast_priv *priv = qdisc_priv(qdisc);
	struct skb_array *q = band2list(priv, band);
	unsigned int pkt_len = qdisc_pkt_len(skb);
	int err;

	err = skb_array_produce(q, skb);

	if (unlikely(err)) {
		if (qdisc_is_percpu_stats(qdisc))
			return qdisc_drop_cpu(skb, qdisc, to_free);
		else
			return qdisc_drop(skb, qdisc, to_free);
	}

	qdisc_update_stats_at_enqueue(qdisc, pkt_len);
	return NET_XMIT_SUCCESS;
}