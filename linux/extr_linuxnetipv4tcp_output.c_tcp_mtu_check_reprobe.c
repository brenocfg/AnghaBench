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
typedef  int u32 ;
struct tcphdr {int dummy; } ;
struct TYPE_6__ {scalar_t__ mss_clamp; } ;
struct tcp_sock {TYPE_2__ rx_opt; } ;
struct sock {int dummy; } ;
struct TYPE_5__ {int sysctl_tcp_probe_interval; } ;
struct net {TYPE_1__ ipv4; } ;
struct TYPE_8__ {void* probe_timestamp; int /*<<< orphan*/  search_low; scalar_t__ search_high; scalar_t__ probe_size; } ;
struct inet_connection_sock {TYPE_4__ icsk_mtup; TYPE_3__* icsk_af_ops; } ;
typedef  int s32 ;
struct TYPE_7__ {scalar_t__ net_header_len; } ;

/* Variables and functions */
 int HZ ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct net* sock_net (struct sock*) ; 
 int tcp_current_mss (struct sock*) ; 
 void* tcp_jiffies32 ; 
 int /*<<< orphan*/  tcp_mss_to_mtu (struct sock*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void tcp_mtu_check_reprobe(struct sock *sk)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	struct net *net = sock_net(sk);
	u32 interval;
	s32 delta;

	interval = net->ipv4.sysctl_tcp_probe_interval;
	delta = tcp_jiffies32 - icsk->icsk_mtup.probe_timestamp;
	if (unlikely(delta >= interval * HZ)) {
		int mss = tcp_current_mss(sk);

		/* Update current search range */
		icsk->icsk_mtup.probe_size = 0;
		icsk->icsk_mtup.search_high = tp->rx_opt.mss_clamp +
			sizeof(struct tcphdr) +
			icsk->icsk_af_ops->net_header_len;
		icsk->icsk_mtup.search_low = tcp_mss_to_mtu(sk, mss);

		/* Update probe time stamp */
		icsk->icsk_mtup.probe_timestamp = tcp_jiffies32;
	}
}