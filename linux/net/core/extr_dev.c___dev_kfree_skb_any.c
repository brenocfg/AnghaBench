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
typedef  enum skb_free_reason { ____Placeholder_skb_free_reason } skb_free_reason ;

/* Variables and functions */
 int /*<<< orphan*/  __dev_kfree_skb_irq (struct sk_buff*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ in_irq () ; 
 scalar_t__ irqs_disabled () ; 

void __dev_kfree_skb_any(struct sk_buff *skb, enum skb_free_reason reason)
{
	if (in_irq() || irqs_disabled())
		__dev_kfree_skb_irq(skb, reason);
	else
		dev_kfree_skb(skb);
}