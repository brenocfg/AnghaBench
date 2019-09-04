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
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int x25_process_rx_frame (struct sock*,struct sk_buff*) ; 

int x25_backlog_rcv(struct sock *sk, struct sk_buff *skb)
{
	int queued = x25_process_rx_frame(sk, skb);

	if (!queued)
		kfree_skb(skb);

	return 0;
}