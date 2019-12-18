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
typedef  size_t u16 ;
struct sk_buff {int dummy; } ;
struct gred_sched_data {int /*<<< orphan*/  vars; scalar_t__ backlog; } ;
struct gred_sched {size_t DPs; int /*<<< orphan*/  wred_set; struct gred_sched_data** tab; } ;
struct TYPE_2__ {int /*<<< orphan*/  backlog; } ;
struct Qdisc {TYPE_1__ qstats; } ;

/* Variables and functions */
 scalar_t__ gred_wred_mode (struct gred_sched*) ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,size_t) ; 
 struct sk_buff* qdisc_dequeue_head (struct Qdisc*) ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 
 struct gred_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  red_start_of_idle_period (int /*<<< orphan*/ *) ; 
 size_t tc_index_to_dp (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *gred_dequeue(struct Qdisc *sch)
{
	struct sk_buff *skb;
	struct gred_sched *t = qdisc_priv(sch);

	skb = qdisc_dequeue_head(sch);

	if (skb) {
		struct gred_sched_data *q;
		u16 dp = tc_index_to_dp(skb);

		if (dp >= t->DPs || (q = t->tab[dp]) == NULL) {
			net_warn_ratelimited("GRED: Unable to relocate VQ 0x%x after dequeue, screwing up backlog\n",
					     tc_index_to_dp(skb));
		} else {
			q->backlog -= qdisc_pkt_len(skb);

			if (gred_wred_mode(t)) {
				if (!sch->qstats.backlog)
					red_start_of_idle_period(&t->wred_set);
			} else {
				if (!q->backlog)
					red_start_of_idle_period(&q->vars);
			}
		}

		return skb;
	}

	return NULL;
}