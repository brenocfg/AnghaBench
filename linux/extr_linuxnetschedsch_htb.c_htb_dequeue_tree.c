#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct htb_sched {int* row_mask; struct htb_level* hlevel; } ;
struct htb_prio {int /*<<< orphan*/  ptr; } ;
struct htb_level {struct htb_prio* hprio; } ;
struct TYPE_15__ {scalar_t__* deficit; TYPE_8__* q; } ;
struct TYPE_16__ {TYPE_6__ leaf; } ;
struct htb_class {scalar_t__ quantum; TYPE_7__ un; TYPE_4__* parent; int /*<<< orphan*/  bstats; } ;
struct TYPE_14__ {scalar_t__ qlen; } ;
struct TYPE_17__ {TYPE_5__ q; struct sk_buff* (* dequeue ) (TYPE_8__*) ;} ;
struct TYPE_11__ {TYPE_1__* clprio; } ;
struct TYPE_12__ {TYPE_2__ inner; } ;
struct TYPE_13__ {TYPE_3__ un; } ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstats_update (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  htb_charge_class (struct htb_sched*,struct htb_class*,int const,struct sk_buff*) ; 
 int /*<<< orphan*/  htb_deactivate (struct htb_sched*,struct htb_class*) ; 
 struct htb_class* htb_lookup_leaf (struct htb_prio*,int const) ; 
 int /*<<< orphan*/  htb_next_rb_node (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_warn_nonwc (char*,TYPE_8__*) ; 
 struct sk_buff* stub1 (TYPE_8__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct sk_buff *htb_dequeue_tree(struct htb_sched *q, const int prio,
					const int level)
{
	struct sk_buff *skb = NULL;
	struct htb_class *cl, *start;
	struct htb_level *hlevel = &q->hlevel[level];
	struct htb_prio *hprio = &hlevel->hprio[prio];

	/* look initial class up in the row */
	start = cl = htb_lookup_leaf(hprio, prio);

	do {
next:
		if (unlikely(!cl))
			return NULL;

		/* class can be empty - it is unlikely but can be true if leaf
		 * qdisc drops packets in enqueue routine or if someone used
		 * graft operation on the leaf since last dequeue;
		 * simply deactivate and skip such class
		 */
		if (unlikely(cl->un.leaf.q->q.qlen == 0)) {
			struct htb_class *next;
			htb_deactivate(q, cl);

			/* row/level might become empty */
			if ((q->row_mask[level] & (1 << prio)) == 0)
				return NULL;

			next = htb_lookup_leaf(hprio, prio);

			if (cl == start)	/* fix start if we just deleted it */
				start = next;
			cl = next;
			goto next;
		}

		skb = cl->un.leaf.q->dequeue(cl->un.leaf.q);
		if (likely(skb != NULL))
			break;

		qdisc_warn_nonwc("htb", cl->un.leaf.q);
		htb_next_rb_node(level ? &cl->parent->un.inner.clprio[prio].ptr:
					 &q->hlevel[0].hprio[prio].ptr);
		cl = htb_lookup_leaf(hprio, prio);

	} while (cl != start);

	if (likely(skb != NULL)) {
		bstats_update(&cl->bstats, skb);
		cl->un.leaf.deficit[level] -= qdisc_pkt_len(skb);
		if (cl->un.leaf.deficit[level] < 0) {
			cl->un.leaf.deficit[level] += cl->quantum;
			htb_next_rb_node(level ? &cl->parent->un.inner.clprio[prio].ptr :
						 &q->hlevel[0].hprio[prio].ptr);
		}
		/* this used to be after charge_class but this constelation
		 * gives us slightly better performance
		 */
		if (!cl->un.leaf.q->q.qlen)
			htb_deactivate(q, cl);
		htb_charge_class(q, cl, level, skb);
	}
	return skb;
}