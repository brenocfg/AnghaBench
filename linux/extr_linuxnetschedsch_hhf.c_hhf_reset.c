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
 struct sk_buff* hhf_dequeue (struct Qdisc*) ; 
 int /*<<< orphan*/  rtnl_kfree_skbs (struct sk_buff*,struct sk_buff*) ; 

__attribute__((used)) static void hhf_reset(struct Qdisc *sch)
{
	struct sk_buff *skb;

	while ((skb = hhf_dequeue(sch)) != NULL)
		rtnl_kfree_skbs(skb, skb);
}