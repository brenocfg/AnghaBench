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
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int PFIFO_FAST_BANDS ; 
 struct sk_buff* __skb_array_peek (struct skb_array*) ; 
 struct skb_array* band2list (struct pfifo_fast_priv*,int) ; 
 struct pfifo_fast_priv* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static struct sk_buff *pfifo_fast_peek(struct Qdisc *qdisc)
{
	struct pfifo_fast_priv *priv = qdisc_priv(qdisc);
	struct sk_buff *skb = NULL;
	int band;

	for (band = 0; band < PFIFO_FAST_BANDS && !skb; band++) {
		struct skb_array *q = band2list(priv, band);

		skb = __skb_array_peek(q);
	}

	return skb;
}