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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int dccph_doff; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 TYPE_1__* dccp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void dccp_enqueue_skb(struct sock *sk, struct sk_buff *skb)
{
	__skb_pull(skb, dccp_hdr(skb)->dccph_doff * 4);
	__skb_queue_tail(&sk->sk_receive_queue, skb);
	skb_set_owner_r(skb, sk);
	sk->sk_data_ready(sk);
}