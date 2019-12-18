#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct hfsc_sched {int /*<<< orphan*/  root; } ;
struct hfsc_class {int cl_flags; TYPE_3__* qdisc; int /*<<< orphan*/  cl_cumul; int /*<<< orphan*/  bstats; } ;
struct TYPE_7__ {scalar_t__ qlen; } ;
struct Qdisc {TYPE_2__ q; } ;
struct TYPE_6__ {scalar_t__ qlen; } ;
struct TYPE_8__ {TYPE_1__ q; } ;

/* Variables and functions */
 int HFSC_RSC ; 
 int /*<<< orphan*/  bstats_update (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct hfsc_class* eltree_get_mindl (struct hfsc_sched*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eltree_remove (struct hfsc_class*) ; 
 int /*<<< orphan*/  hfsc_schedule_watchdog (struct Qdisc*) ; 
 int /*<<< orphan*/  psched_get_time () ; 
 int /*<<< orphan*/  qdisc_bstats_update (struct Qdisc*,struct sk_buff*) ; 
 struct sk_buff* qdisc_dequeue_peeked (TYPE_3__*) ; 
 unsigned int qdisc_peek_len (TYPE_3__*) ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 
 struct hfsc_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_dec (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_overlimit (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_warn_nonwc (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  update_d (struct hfsc_class*,unsigned int) ; 
 int /*<<< orphan*/  update_ed (struct hfsc_class*,unsigned int) ; 
 int /*<<< orphan*/  update_vf (struct hfsc_class*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct hfsc_class* vttree_get_minvt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
hfsc_dequeue(struct Qdisc *sch)
{
	struct hfsc_sched *q = qdisc_priv(sch);
	struct hfsc_class *cl;
	struct sk_buff *skb;
	u64 cur_time;
	unsigned int next_len;
	int realtime = 0;

	if (sch->q.qlen == 0)
		return NULL;

	cur_time = psched_get_time();

	/*
	 * if there are eligible classes, use real-time criteria.
	 * find the class with the minimum deadline among
	 * the eligible classes.
	 */
	cl = eltree_get_mindl(q, cur_time);
	if (cl) {
		realtime = 1;
	} else {
		/*
		 * use link-sharing criteria
		 * get the class with the minimum vt in the hierarchy
		 */
		cl = vttree_get_minvt(&q->root, cur_time);
		if (cl == NULL) {
			qdisc_qstats_overlimit(sch);
			hfsc_schedule_watchdog(sch);
			return NULL;
		}
	}

	skb = qdisc_dequeue_peeked(cl->qdisc);
	if (skb == NULL) {
		qdisc_warn_nonwc("HFSC", cl->qdisc);
		return NULL;
	}

	bstats_update(&cl->bstats, skb);
	update_vf(cl, qdisc_pkt_len(skb), cur_time);
	if (realtime)
		cl->cl_cumul += qdisc_pkt_len(skb);

	if (cl->cl_flags & HFSC_RSC) {
		if (cl->qdisc->q.qlen != 0) {
			/* update ed */
			next_len = qdisc_peek_len(cl->qdisc);
			if (realtime)
				update_ed(cl, next_len);
			else
				update_d(cl, next_len);
		} else {
			/* the class becomes passive */
			eltree_remove(cl);
		}
	}

	qdisc_bstats_update(sch, skb);
	qdisc_qstats_backlog_dec(sch, skb);
	sch->q.qlen--;

	return skb;
}