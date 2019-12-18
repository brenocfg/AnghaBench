#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct tcf_proto {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  childdrop; int /*<<< orphan*/  earlydrop; int /*<<< orphan*/  marked; int /*<<< orphan*/  penaltydrop; int /*<<< orphan*/  bucketdrop; int /*<<< orphan*/  queuedrop; } ;
struct sfb_sched_data {size_t slot; scalar_t__ limit; unsigned long rehash_interval; unsigned long rehash_time; int double_buffering; unsigned long warmup_time; scalar_t__ bin_size; size_t max; TYPE_3__ stats; TYPE_1__* bins; int /*<<< orphan*/  filter_list; struct Qdisc* qdisc; } ;
struct sfb_bucket {scalar_t__ qlen; size_t p_mark; } ;
struct TYPE_6__ {scalar_t__ qlen; } ;
struct Qdisc {TYPE_2__ q; } ;
struct TYPE_8__ {size_t* hashes; } ;
struct TYPE_5__ {struct sfb_bucket** bins; int /*<<< orphan*/  perturbation; } ;

/* Variables and functions */
 scalar_t__ INET_ECN_set_ce (struct sk_buff*) ; 
 int NET_XMIT_CN ; 
 int NET_XMIT_SUCCESS ; 
 size_t SFB_BUCKET_MASK ; 
 size_t SFB_BUCKET_SHIFT ; 
 int SFB_LEVELS ; 
 size_t SFB_MAX_PROB ; 
 int __NET_XMIT_BYPASS ; 
 int /*<<< orphan*/  decrement_prob (struct sfb_bucket*,struct sfb_sched_data*) ; 
 int /*<<< orphan*/  increment_prob (struct sfb_bucket*,struct sfb_sched_data*) ; 
 int /*<<< orphan*/  increment_qlen (struct sk_buff*,struct sfb_sched_data*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ net_xmit_drop_count (int) ; 
 size_t prandom_u32 () ; 
 int /*<<< orphan*/  qdisc_drop (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 int qdisc_enqueue (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 
 struct sfb_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_inc (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_drop (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_overlimit (struct Qdisc*) ; 
 struct tcf_proto* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfb_classify (struct sk_buff*,struct tcf_proto*,int*,size_t*) ; 
 scalar_t__ sfb_rate_limit (struct sk_buff*,struct sfb_sched_data*) ; 
 TYPE_4__* sfb_skb_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  sfb_swap_slot (struct sfb_sched_data*) ; 
 size_t siphash_1u32 (size_t,int /*<<< orphan*/ *) ; 
 size_t skb_get_hash_perturb (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int time_after (unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sfb_enqueue(struct sk_buff *skb, struct Qdisc *sch,
		       struct sk_buff **to_free)
{

	struct sfb_sched_data *q = qdisc_priv(sch);
	struct Qdisc *child = q->qdisc;
	struct tcf_proto *fl;
	int i;
	u32 p_min = ~0;
	u32 minqlen = ~0;
	u32 r, sfbhash;
	u32 slot = q->slot;
	int ret = NET_XMIT_SUCCESS | __NET_XMIT_BYPASS;

	if (unlikely(sch->q.qlen >= q->limit)) {
		qdisc_qstats_overlimit(sch);
		q->stats.queuedrop++;
		goto drop;
	}

	if (q->rehash_interval > 0) {
		unsigned long limit = q->rehash_time + q->rehash_interval;

		if (unlikely(time_after(jiffies, limit))) {
			sfb_swap_slot(q);
			q->rehash_time = jiffies;
		} else if (unlikely(!q->double_buffering && q->warmup_time > 0 &&
				    time_after(jiffies, limit - q->warmup_time))) {
			q->double_buffering = true;
		}
	}

	fl = rcu_dereference_bh(q->filter_list);
	if (fl) {
		u32 salt;

		/* If using external classifiers, get result and record it. */
		if (!sfb_classify(skb, fl, &ret, &salt))
			goto other_drop;
		sfbhash = siphash_1u32(salt, &q->bins[slot].perturbation);
	} else {
		sfbhash = skb_get_hash_perturb(skb, &q->bins[slot].perturbation);
	}


	if (!sfbhash)
		sfbhash = 1;
	sfb_skb_cb(skb)->hashes[slot] = sfbhash;

	for (i = 0; i < SFB_LEVELS; i++) {
		u32 hash = sfbhash & SFB_BUCKET_MASK;
		struct sfb_bucket *b = &q->bins[slot].bins[i][hash];

		sfbhash >>= SFB_BUCKET_SHIFT;
		if (b->qlen == 0)
			decrement_prob(b, q);
		else if (b->qlen >= q->bin_size)
			increment_prob(b, q);
		if (minqlen > b->qlen)
			minqlen = b->qlen;
		if (p_min > b->p_mark)
			p_min = b->p_mark;
	}

	slot ^= 1;
	sfb_skb_cb(skb)->hashes[slot] = 0;

	if (unlikely(minqlen >= q->max)) {
		qdisc_qstats_overlimit(sch);
		q->stats.bucketdrop++;
		goto drop;
	}

	if (unlikely(p_min >= SFB_MAX_PROB)) {
		/* Inelastic flow */
		if (q->double_buffering) {
			sfbhash = skb_get_hash_perturb(skb,
			    &q->bins[slot].perturbation);
			if (!sfbhash)
				sfbhash = 1;
			sfb_skb_cb(skb)->hashes[slot] = sfbhash;

			for (i = 0; i < SFB_LEVELS; i++) {
				u32 hash = sfbhash & SFB_BUCKET_MASK;
				struct sfb_bucket *b = &q->bins[slot].bins[i][hash];

				sfbhash >>= SFB_BUCKET_SHIFT;
				if (b->qlen == 0)
					decrement_prob(b, q);
				else if (b->qlen >= q->bin_size)
					increment_prob(b, q);
			}
		}
		if (sfb_rate_limit(skb, q)) {
			qdisc_qstats_overlimit(sch);
			q->stats.penaltydrop++;
			goto drop;
		}
		goto enqueue;
	}

	r = prandom_u32() & SFB_MAX_PROB;

	if (unlikely(r < p_min)) {
		if (unlikely(p_min > SFB_MAX_PROB / 2)) {
			/* If we're marking that many packets, then either
			 * this flow is unresponsive, or we're badly congested.
			 * In either case, we want to start dropping packets.
			 */
			if (r < (p_min - SFB_MAX_PROB / 2) * 2) {
				q->stats.earlydrop++;
				goto drop;
			}
		}
		if (INET_ECN_set_ce(skb)) {
			q->stats.marked++;
		} else {
			q->stats.earlydrop++;
			goto drop;
		}
	}

enqueue:
	ret = qdisc_enqueue(skb, child, to_free);
	if (likely(ret == NET_XMIT_SUCCESS)) {
		qdisc_qstats_backlog_inc(sch, skb);
		sch->q.qlen++;
		increment_qlen(skb, q);
	} else if (net_xmit_drop_count(ret)) {
		q->stats.childdrop++;
		qdisc_qstats_drop(sch);
	}
	return ret;

drop:
	qdisc_drop(skb, sch, to_free);
	return NET_XMIT_CN;
other_drop:
	if (ret & __NET_XMIT_BYPASS)
		qdisc_qstats_drop(sch);
	kfree_skb(skb);
	return ret;
}