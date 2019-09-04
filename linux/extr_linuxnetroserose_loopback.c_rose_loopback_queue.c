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
struct rose_neigh {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  loopback_queue ; 
 int /*<<< orphan*/  rose_loopback_running () ; 
 int /*<<< orphan*/  rose_set_loopback_timer () ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int rose_loopback_queue(struct sk_buff *skb, struct rose_neigh *neigh)
{
	struct sk_buff *skbn;

	skbn = skb_clone(skb, GFP_ATOMIC);

	kfree_skb(skb);

	if (skbn != NULL) {
		skb_queue_tail(&loopback_queue, skbn);

		if (!rose_loopback_running())
			rose_set_loopback_timer();
	}

	return 1;
}