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
struct sk_buff {scalar_t__ protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_unicast_destination (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp6_request_sock_ops ; 
 int tcp_conn_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_listendrop (struct sock*) ; 
 int /*<<< orphan*/  tcp_request_sock_ipv6_ops ; 
 int tcp_v4_conn_request (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static int tcp_v6_conn_request(struct sock *sk, struct sk_buff *skb)
{
	if (skb->protocol == htons(ETH_P_IP))
		return tcp_v4_conn_request(sk, skb);

	if (!ipv6_unicast_destination(skb))
		goto drop;

	return tcp_conn_request(&tcp6_request_sock_ops,
				&tcp_request_sock_ipv6_ops, sk, skb);

drop:
	tcp_listendrop(sk);
	return 0; /* don't send reset */
}