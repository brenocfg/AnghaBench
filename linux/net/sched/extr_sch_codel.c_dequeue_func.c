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
struct sk_buff {int /*<<< orphan*/  end; } ;
struct codel_vars {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  backlog; } ;
struct Qdisc {TYPE_1__ qstats; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 struct sk_buff* __qdisc_dequeue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 scalar_t__ qdisc_pkt_len (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *dequeue_func(struct codel_vars *vars, void *ctx)
{
	struct Qdisc *sch = ctx;
	struct sk_buff *skb = __qdisc_dequeue_head(&sch->q);

	if (skb) {
		sch->qstats.backlog -= qdisc_pkt_len(skb);
		prefetch(&skb->end); /* we'll need skb_shinfo() */
	}
	return skb;
}