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
struct sock {struct sk_buff* sk_send_head; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (struct sk_buff*) ; 
 int /*<<< orphan*/  gfp_any () ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 

__attribute__((used)) static struct sk_buff *dccp_skb_entail(struct sock *sk, struct sk_buff *skb)
{
	skb_set_owner_w(skb, sk);
	WARN_ON(sk->sk_send_head);
	sk->sk_send_head = skb;
	return skb_clone(sk->sk_send_head, gfp_any());
}