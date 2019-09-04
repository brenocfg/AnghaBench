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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 

__attribute__((used)) static void pneigh_queue_purge(struct sk_buff_head *list)
{
	struct sk_buff *skb;

	while ((skb = skb_dequeue(list)) != NULL) {
		dev_put(skb->dev);
		kfree_skb(skb);
	}
}