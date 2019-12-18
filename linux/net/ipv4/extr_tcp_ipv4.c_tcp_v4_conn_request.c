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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int rt_flags; } ;

/* Variables and functions */
 int RTCF_BROADCAST ; 
 int RTCF_MULTICAST ; 
 TYPE_1__* skb_rtable (struct sk_buff*) ; 
 int tcp_conn_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_listendrop (struct sock*) ; 
 int /*<<< orphan*/  tcp_request_sock_ipv4_ops ; 
 int /*<<< orphan*/  tcp_request_sock_ops ; 

int tcp_v4_conn_request(struct sock *sk, struct sk_buff *skb)
{
	/* Never answer to SYNs send to broadcast or multicast */
	if (skb_rtable(skb)->rt_flags & (RTCF_BROADCAST | RTCF_MULTICAST))
		goto drop;

	return tcp_conn_request(&tcp_request_sock_ops,
				&tcp_request_sock_ipv4_ops, sk, skb);

drop:
	tcp_listendrop(sk);
	return 0;
}