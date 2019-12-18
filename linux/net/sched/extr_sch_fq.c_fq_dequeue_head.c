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
struct sk_buff {int dummy; } ;
struct fq_flow {int /*<<< orphan*/  qlen; } ;
struct TYPE_2__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  fq_erase_head (struct Qdisc*,struct fq_flow*,struct sk_buff*) ; 
 struct sk_buff* fq_peek (struct fq_flow*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_dec (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_mark_not_on_list (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *fq_dequeue_head(struct Qdisc *sch, struct fq_flow *flow)
{
	struct sk_buff *skb = fq_peek(flow);

	if (skb) {
		fq_erase_head(sch, flow, skb);
		skb_mark_not_on_list(skb);
		flow->qlen--;
		qdisc_qstats_backlog_dec(sch, skb);
		sch->q.qlen--;
	}
	return skb;
}