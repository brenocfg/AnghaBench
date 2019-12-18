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
struct sock {int /*<<< orphan*/  sk_num; } ;
struct request_sock_queue {int /*<<< orphan*/  synflood_warned; } ;
struct TYPE_3__ {int sysctl_tcp_syncookies; } ;
struct net {TYPE_1__ ipv4; } ;
struct TYPE_4__ {struct request_sock_queue icsk_accept_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_TCPREQQFULLDOCOOKIES ; 
 int /*<<< orphan*/  LINUX_MIB_TCPREQQFULLDROP ; 
 int /*<<< orphan*/  __NET_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 TYPE_2__* inet_csk (struct sock const*) ; 
 int /*<<< orphan*/  net_info_ratelimited (char*,char const*,int /*<<< orphan*/ ,char const*) ; 
 struct net* sock_net (struct sock const*) ; 
 scalar_t__ xchg (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool tcp_syn_flood_action(const struct sock *sk, const char *proto)
{
	struct request_sock_queue *queue = &inet_csk(sk)->icsk_accept_queue;
	const char *msg = "Dropping request";
	bool want_cookie = false;
	struct net *net = sock_net(sk);

#ifdef CONFIG_SYN_COOKIES
	if (net->ipv4.sysctl_tcp_syncookies) {
		msg = "Sending cookies";
		want_cookie = true;
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPREQQFULLDOCOOKIES);
	} else
#endif
		__NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPREQQFULLDROP);

	if (!queue->synflood_warned &&
	    net->ipv4.sysctl_tcp_syncookies != 2 &&
	    xchg(&queue->synflood_warned, 1) == 0)
		net_info_ratelimited("%s: Possible SYN flooding on port %d. %s.  Check SNMP counters.\n",
				     proto, sk->sk_num, msg);

	return want_cookie;
}