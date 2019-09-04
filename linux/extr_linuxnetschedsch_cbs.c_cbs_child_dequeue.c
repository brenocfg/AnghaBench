#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  qlen; } ;
struct Qdisc {TYPE_2__ q; TYPE_1__* ops; } ;
struct TYPE_3__ {struct sk_buff* (* dequeue ) (struct Qdisc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  qdisc_bstats_update (struct Qdisc*,struct sk_buff*) ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_dec (struct Qdisc*,struct sk_buff*) ; 
 struct sk_buff* stub1 (struct Qdisc*) ; 

__attribute__((used)) static struct sk_buff *cbs_child_dequeue(struct Qdisc *sch, struct Qdisc *child)
{
	struct sk_buff *skb;

	skb = child->ops->dequeue(child);
	if (!skb)
		return NULL;

	qdisc_qstats_backlog_dec(sch, skb);
	qdisc_bstats_update(sch, skb);
	sch->q.qlen--;

	return skb;
}