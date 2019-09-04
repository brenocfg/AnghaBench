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
struct pfifo_fast_priv {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PFIFO_FAST_BANDS ; 
 struct skb_array* band2list (struct pfifo_fast_priv*,int) ; 
 struct pfifo_fast_priv* qdisc_priv (struct Qdisc*) ; 
 int skb_array_resize_multiple (struct skb_array**,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pfifo_fast_change_tx_queue_len(struct Qdisc *sch,
					  unsigned int new_len)
{
	struct pfifo_fast_priv *priv = qdisc_priv(sch);
	struct skb_array *bands[PFIFO_FAST_BANDS];
	int prio;

	for (prio = 0; prio < PFIFO_FAST_BANDS; prio++) {
		struct skb_array *q = band2list(priv, prio);

		bands[prio] = q;
	}

	return skb_array_resize_multiple(bands, PFIFO_FAST_BANDS, new_len,
					 GFP_KERNEL);
}