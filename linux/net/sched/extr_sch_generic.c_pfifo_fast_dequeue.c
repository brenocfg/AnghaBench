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
struct sk_buff {int dummy; } ;
struct pfifo_fast_priv {int dummy; } ;
struct Qdisc {int empty; } ;

/* Variables and functions */
 int PFIFO_FAST_BANDS ; 
 struct sk_buff* __skb_array_consume (struct skb_array*) ; 
 scalar_t__ __skb_array_empty (struct skb_array*) ; 
 struct skb_array* band2list (struct pfifo_fast_priv*,int) ; 
 scalar_t__ likely (struct sk_buff*) ; 
 struct pfifo_fast_priv* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_update_stats_at_dequeue (struct Qdisc*,struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *pfifo_fast_dequeue(struct Qdisc *qdisc)
{
	struct pfifo_fast_priv *priv = qdisc_priv(qdisc);
	struct sk_buff *skb = NULL;
	int band;

	for (band = 0; band < PFIFO_FAST_BANDS && !skb; band++) {
		struct skb_array *q = band2list(priv, band);

		if (__skb_array_empty(q))
			continue;

		skb = __skb_array_consume(q);
	}
	if (likely(skb)) {
		qdisc_update_stats_at_dequeue(qdisc, skb);
	} else {
		qdisc->empty = true;
	}

	return skb;
}