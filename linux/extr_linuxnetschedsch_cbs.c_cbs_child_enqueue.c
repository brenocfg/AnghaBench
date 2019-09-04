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
struct TYPE_3__ {int (* enqueue ) (struct sk_buff*,struct Qdisc*,struct sk_buff**) ;} ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
 int /*<<< orphan*/  qdisc_qstats_backlog_inc (struct Qdisc*,struct sk_buff*) ; 
 int stub1 (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 

__attribute__((used)) static int cbs_child_enqueue(struct sk_buff *skb, struct Qdisc *sch,
			     struct Qdisc *child,
			     struct sk_buff **to_free)
{
	int err;

	err = child->ops->enqueue(skb, child, to_free);
	if (err != NET_XMIT_SUCCESS)
		return err;

	qdisc_qstats_backlog_inc(sch, skb);
	sch->q.qlen++;

	return NET_XMIT_SUCCESS;
}