#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcp_sock {int /*<<< orphan*/  reord_seen; scalar_t__ packets_out; int /*<<< orphan*/  reordering; } ;
struct sock {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sysctl_tcp_max_reordering; } ;
struct TYPE_5__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINUX_MIB_TCPRENOREORDER ; 
 int /*<<< orphan*/  NET_INC_STATS (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* sock_net (struct sock*) ; 
 int /*<<< orphan*/  tcp_limit_reno_sacked (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void tcp_check_reno_reordering(struct sock *sk, const int addend)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (!tcp_limit_reno_sacked(tp))
		return;

	tp->reordering = min_t(u32, tp->packets_out + addend,
			       sock_net(sk)->ipv4.sysctl_tcp_max_reordering);
	tp->reord_seen++;
	NET_INC_STATS(sock_net(sk), LINUX_MIB_TCPRENOREORDER);
}