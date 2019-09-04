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
struct sock {int dummy; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct inet_cork {int dummy; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue_tail (struct sk_buff_head*) ; 
 int /*<<< orphan*/  ip_cork_release (struct inet_cork*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static void __ip_flush_pending_frames(struct sock *sk,
				      struct sk_buff_head *queue,
				      struct inet_cork *cork)
{
	struct sk_buff *skb;

	while ((skb = __skb_dequeue_tail(queue)) != NULL)
		kfree_skb(skb);

	ip_cork_release(cork);
}