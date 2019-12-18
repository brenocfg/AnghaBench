#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int tcp_flags; } ;
struct TYPE_4__ {scalar_t__ sysctl_tcp_ecn_fallback; } ;
struct TYPE_5__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int TCPHDR_CWR ; 
 int TCPHDR_ECE ; 
 TYPE_3__* TCP_SKB_CB (struct sk_buff*) ; 
 TYPE_2__* sock_net (struct sock*) ; 

__attribute__((used)) static void tcp_ecn_clear_syn(struct sock *sk, struct sk_buff *skb)
{
	if (sock_net(sk)->ipv4.sysctl_tcp_ecn_fallback)
		/* tp->ecn_flags are cleared at a later point in time when
		 * SYN ACK is ultimatively being received.
		 */
		TCP_SKB_CB(skb)->tcp_flags &= ~(TCPHDR_ECE | TCPHDR_CWR);
}