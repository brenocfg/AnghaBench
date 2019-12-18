#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct red_parms {scalar_t__ qth_min; scalar_t__ qth_max; } ;
struct TYPE_9__ {int /*<<< orphan*/  pdrop; int /*<<< orphan*/  prob_mark; int /*<<< orphan*/  prob_drop; int /*<<< orphan*/  forced_mark; int /*<<< orphan*/  forced_drop; int /*<<< orphan*/  matched; } ;
struct TYPE_10__ {scalar_t__ qavg; int qcount; void* qR; } ;
struct choke_sched_data {scalar_t__ limit; size_t tail; int tab_mask; TYPE_2__ stats; struct sk_buff** tab; TYPE_3__ vars; struct red_parms parms; } ;
struct TYPE_8__ {scalar_t__ qlen; } ;
struct Qdisc {TYPE_1__ q; } ;
struct TYPE_11__ {scalar_t__ keys_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  INET_ECN_set_ce (struct sk_buff*) ; 
 int NET_XMIT_CN ; 
 int NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  choke_drop_by_idx (struct Qdisc*,unsigned int,struct sk_buff**) ; 
 scalar_t__ choke_match_random (struct choke_sched_data*,struct sk_buff*,unsigned int*) ; 
 TYPE_7__* choke_skb_cb (struct sk_buff*) ; 
 int qdisc_drop (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 struct choke_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_inc (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_overlimit (struct Qdisc*) ; 
 scalar_t__ red_calc_qavg (struct red_parms const*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  red_end_of_idle_period (TYPE_3__*) ; 
 scalar_t__ red_is_idling (TYPE_3__*) ; 
 scalar_t__ red_mark_probability (struct red_parms const*,TYPE_3__*,scalar_t__) ; 
 void* red_random (struct red_parms const*) ; 
 int /*<<< orphan*/  use_ecn (struct choke_sched_data*) ; 
 scalar_t__ use_harddrop (struct choke_sched_data*) ; 

__attribute__((used)) static int choke_enqueue(struct sk_buff *skb, struct Qdisc *sch,
			 struct sk_buff **to_free)
{
	struct choke_sched_data *q = qdisc_priv(sch);
	const struct red_parms *p = &q->parms;

	choke_skb_cb(skb)->keys_valid = 0;
	/* Compute average queue usage (see RED) */
	q->vars.qavg = red_calc_qavg(p, &q->vars, sch->q.qlen);
	if (red_is_idling(&q->vars))
		red_end_of_idle_period(&q->vars);

	/* Is queue small? */
	if (q->vars.qavg <= p->qth_min)
		q->vars.qcount = -1;
	else {
		unsigned int idx;

		/* Draw a packet at random from queue and compare flow */
		if (choke_match_random(q, skb, &idx)) {
			q->stats.matched++;
			choke_drop_by_idx(sch, idx, to_free);
			goto congestion_drop;
		}

		/* Queue is large, always mark/drop */
		if (q->vars.qavg > p->qth_max) {
			q->vars.qcount = -1;

			qdisc_qstats_overlimit(sch);
			if (use_harddrop(q) || !use_ecn(q) ||
			    !INET_ECN_set_ce(skb)) {
				q->stats.forced_drop++;
				goto congestion_drop;
			}

			q->stats.forced_mark++;
		} else if (++q->vars.qcount) {
			if (red_mark_probability(p, &q->vars, q->vars.qavg)) {
				q->vars.qcount = 0;
				q->vars.qR = red_random(p);

				qdisc_qstats_overlimit(sch);
				if (!use_ecn(q) || !INET_ECN_set_ce(skb)) {
					q->stats.prob_drop++;
					goto congestion_drop;
				}

				q->stats.prob_mark++;
			}
		} else
			q->vars.qR = red_random(p);
	}

	/* Admit new packet */
	if (sch->q.qlen < q->limit) {
		q->tab[q->tail] = skb;
		q->tail = (q->tail + 1) & q->tab_mask;
		++sch->q.qlen;
		qdisc_qstats_backlog_inc(sch, skb);
		return NET_XMIT_SUCCESS;
	}

	q->stats.pdrop++;
	return qdisc_drop(skb, sch, to_free);

congestion_drop:
	qdisc_drop(skb, sch, to_free);
	return NET_XMIT_CN;
}