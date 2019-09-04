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
struct Qdisc {int flags; } ;

/* Variables and functions */
 int TCQ_F_NOLOCK ; 
 int __dev_requeue_skb (struct sk_buff*,struct Qdisc*) ; 
 int dev_requeue_skb_locked (struct sk_buff*,struct Qdisc*) ; 

__attribute__((used)) static inline int dev_requeue_skb(struct sk_buff *skb, struct Qdisc *q)
{
	if (q->flags & TCQ_F_NOLOCK)
		return dev_requeue_skb_locked(skb, q);
	else
		return __dev_requeue_skb(skb, q);
}