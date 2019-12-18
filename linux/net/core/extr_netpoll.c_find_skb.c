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
struct sk_buff {int /*<<< orphan*/  users; } ;
struct netpoll {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netpoll_poll_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  refill_skbs () ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pool ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int /*<<< orphan*/  zap_completion_queue () ; 

__attribute__((used)) static struct sk_buff *find_skb(struct netpoll *np, int len, int reserve)
{
	int count = 0;
	struct sk_buff *skb;

	zap_completion_queue();
	refill_skbs();
repeat:

	skb = alloc_skb(len, GFP_ATOMIC);
	if (!skb)
		skb = skb_dequeue(&skb_pool);

	if (!skb) {
		if (++count < 10) {
			netpoll_poll_dev(np->dev);
			goto repeat;
		}
		return NULL;
	}

	refcount_set(&skb->users, 1);
	skb_reserve(skb, reserve);
	return skb;
}