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
typedef  scalar_t__ u32 ;
struct tcp_sock {int /*<<< orphan*/  delivered_ce; scalar_t__ delivered; } ;
struct sock {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int FLAG_ECE ; 
 int /*<<< orphan*/  LINUX_MIB_TCPDELIVERED ; 
 int /*<<< orphan*/  LINUX_MIB_TCPDELIVEREDCE ; 
 int /*<<< orphan*/  NET_ADD_STATS (struct net const*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct net* sock_net (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static u32 tcp_newly_delivered(struct sock *sk, u32 prior_delivered, int flag)
{
	const struct net *net = sock_net(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	u32 delivered;

	delivered = tp->delivered - prior_delivered;
	NET_ADD_STATS(net, LINUX_MIB_TCPDELIVERED, delivered);
	if (flag & FLAG_ECE) {
		tp->delivered_ce += delivered;
		NET_ADD_STATS(net, LINUX_MIB_TCPDELIVEREDCE, delivered);
	}
	return delivered;
}