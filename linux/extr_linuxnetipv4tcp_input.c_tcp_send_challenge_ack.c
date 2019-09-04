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
typedef  int u32 ;
struct tcp_sock {int /*<<< orphan*/  last_oow_ack_time; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int sysctl_tcp_challenge_ack_limit; } ;
struct net {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  LINUX_MIB_TCPACKSKIPPEDCHALLENGE ; 
 int /*<<< orphan*/  LINUX_MIB_TCPCHALLENGEACK ; 
 int /*<<< orphan*/  NET_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int READ_ONCE (unsigned int) ; 
 int /*<<< orphan*/  WRITE_ONCE (unsigned int,int) ; 
 scalar_t__ __tcp_oow_rate_limited (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int jiffies ; 
 int prandom_u32_max (int) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_send_ack (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void tcp_send_challenge_ack(struct sock *sk, const struct sk_buff *skb)
{
	/* unprotected vars, we dont care of overwrites */
	static u32 challenge_timestamp;
	static unsigned int challenge_count;
	struct tcp_sock *tp = tcp_sk(sk);
	struct net *net = sock_net(sk);
	u32 count, now;

	/* First check our per-socket dupack rate limit. */
	if (__tcp_oow_rate_limited(net,
				   LINUX_MIB_TCPACKSKIPPEDCHALLENGE,
				   &tp->last_oow_ack_time))
		return;

	/* Then check host-wide RFC 5961 rate limit. */
	now = jiffies / HZ;
	if (now != challenge_timestamp) {
		u32 ack_limit = net->ipv4.sysctl_tcp_challenge_ack_limit;
		u32 half = (ack_limit + 1) >> 1;

		challenge_timestamp = now;
		WRITE_ONCE(challenge_count, half + prandom_u32_max(ack_limit));
	}
	count = READ_ONCE(challenge_count);
	if (count > 0) {
		WRITE_ONCE(challenge_count, count - 1);
		NET_INC_STATS(net, LINUX_MIB_TCPCHALLENGEACK);
		tcp_send_ack(sk);
	}
}