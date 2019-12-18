#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pie_process_dequeue (struct Qdisc*,struct sk_buff*) ; 
 struct sk_buff* qdisc_dequeue_head (struct Qdisc*) ; 

__attribute__((used)) static struct sk_buff *pie_qdisc_dequeue(struct Qdisc *sch)
{
	struct sk_buff *skb = qdisc_dequeue_head(sch);

	if (!skb)
		return NULL;

	pie_process_dequeue(sch, skb);
	return skb;
}