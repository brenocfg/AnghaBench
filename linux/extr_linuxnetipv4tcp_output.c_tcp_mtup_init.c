#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tcphdr {int dummy; } ;
struct TYPE_5__ {scalar_t__ mss_clamp; } ;
struct tcp_sock {TYPE_1__ rx_opt; } ;
struct sock {int dummy; } ;
struct TYPE_7__ {int sysctl_tcp_mtu_probing; int /*<<< orphan*/  sysctl_tcp_base_mss; } ;
struct net {TYPE_3__ ipv4; } ;
struct TYPE_8__ {int enabled; int /*<<< orphan*/  probe_timestamp; scalar_t__ probe_size; int /*<<< orphan*/  search_low; scalar_t__ search_high; } ;
struct inet_connection_sock {TYPE_4__ icsk_mtup; TYPE_2__* icsk_af_ops; } ;
struct TYPE_6__ {scalar_t__ net_header_len; } ;

/* Variables and functions */
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_jiffies32 ; 
 int /*<<< orphan*/  tcp_mss_to_mtu (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

void tcp_mtup_init(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct net *net = sock_net(sk);

	icsk->icsk_mtup.enabled = net->ipv4.sysctl_tcp_mtu_probing > 1;
	icsk->icsk_mtup.search_high = tp->rx_opt.mss_clamp + sizeof(struct tcphdr) +
			       icsk->icsk_af_ops->net_header_len;
	icsk->icsk_mtup.search_low = tcp_mss_to_mtu(sk, net->ipv4.sysctl_tcp_base_mss);
	icsk->icsk_mtup.probe_size = 0;
	if (icsk->icsk_mtup.enabled)
		icsk->icsk_mtup.probe_timestamp = tcp_jiffies32;
}