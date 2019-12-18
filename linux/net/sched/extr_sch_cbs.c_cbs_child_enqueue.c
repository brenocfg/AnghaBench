#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_5__ {unsigned int backlog; } ;
struct Qdisc {TYPE_3__ q; TYPE_2__ qstats; TYPE_1__* ops; } ;
struct TYPE_4__ {int (* enqueue ) (struct sk_buff*,struct Qdisc*,struct sk_buff**) ;} ;

/* Variables and functions */
 int NET_XMIT_SUCCESS ; 
 unsigned int qdisc_pkt_len (struct sk_buff*) ; 
 int stub1 (struct sk_buff*,struct Qdisc*,struct sk_buff**) ; 

__attribute__((used)) static int cbs_child_enqueue(struct sk_buff *skb, struct Qdisc *sch,
			     struct Qdisc *child,
			     struct sk_buff **to_free)
{
	unsigned int len = qdisc_pkt_len(skb);
	int err;

	err = child->ops->enqueue(skb, child, to_free);
	if (err != NET_XMIT_SUCCESS)
		return err;

	sch->qstats.backlog += len;
	sch->q.qlen++;

	return NET_XMIT_SUCCESS;
}