#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sysctl_tcp_min_snd_mss; int /*<<< orphan*/  sysctl_tcp_mtu_probe_floor; int /*<<< orphan*/  sysctl_tcp_base_mss; int /*<<< orphan*/  sysctl_tcp_mtu_probing; } ;
struct net {TYPE_1__ ipv4; } ;
struct TYPE_4__ {int enabled; int /*<<< orphan*/  search_low; int /*<<< orphan*/  probe_timestamp; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_pmtu_cookie; TYPE_2__ icsk_mtup; } ;

/* Variables and functions */
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_jiffies32 ; 
 int /*<<< orphan*/  tcp_mss_to_mtu (struct sock*,int) ; 
 int tcp_mtu_to_mss (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_sync_mss (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_mtu_probing(struct inet_connection_sock *icsk, struct sock *sk)
{
	const struct net *net = sock_net(sk);
	int mss;

	/* Black hole detection */
	if (!net->ipv4.sysctl_tcp_mtu_probing)
		return;

	if (!icsk->icsk_mtup.enabled) {
		icsk->icsk_mtup.enabled = 1;
		icsk->icsk_mtup.probe_timestamp = tcp_jiffies32;
	} else {
		mss = tcp_mtu_to_mss(sk, icsk->icsk_mtup.search_low) >> 1;
		mss = min(net->ipv4.sysctl_tcp_base_mss, mss);
		mss = max(mss, net->ipv4.sysctl_tcp_mtu_probe_floor);
		mss = max(mss, net->ipv4.sysctl_tcp_min_snd_mss);
		icsk->icsk_mtup.search_low = tcp_mss_to_mtu(sk, mss);
	}
	tcp_sync_mss(sk, icsk->icsk_pmtu_cookie);
}